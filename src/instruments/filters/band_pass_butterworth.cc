#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <boost/math/complex.hpp>
#include <iostream>
#include "../../tnt_ext.h"
#include "band_pass_butterworth.h"

using namespace std;
using namespace TNT;

// Utility function for pre warping a frequency for use in a bilinear transformed filter
double AutoStep::Instruments::BandPassButterworthFilter::Note::bilinear_pre_warp(double input) {
  return (2/time_step)*atan(time_step*input/2);
}

AutoStep::Instruments::BandPassButterworthFilter::Note::Note(boost::intrusive_ptr<AutoStep::Note> &_input, double _centre_freq, double _band_width, unsigned int _order, double _time_step) : AutoStep::Instruments::Filter::Note(_input), centre_freq(_centre_freq), band_width(_band_width), order(_order), time_step(_time_step) {
  calculate_filter_polynomials();
}

boost::intrusive_ptr<AutoStep::Note> AutoStep::Instruments::BandPassButterworthFilter::output(boost::intrusive_ptr<AutoStep::Note> &_input, double _centre_freq, double _band_width, unsigned int _order, double _time_step) {
  return boost::intrusive_ptr<AutoStep::Instruments::BandPassButterworthFilter::Note>(new AutoStep::Instruments::BandPassButterworthFilter::Note(_input, _centre_freq, _band_width, _order, _time_step));
}

double AutoStep::Instruments::BandPassButterworthFilter::Note::output(double time) {

  // Rotate x(t) history
  input_history.push_front(input->output(time));
  input_history.pop_back();

  // Apply the filter polynomials
  double numerator_result = 0e0;
  for (int i=0;i<numerator_polynomial.dim1();i++) {
    numerator_result += input_history[i]*numerator_polynomial[i];
  }

  double denominator_result = 0e0;
  for (int i=0;i<denominator_polynomial.dim1()-1;i++) {
    denominator_result += output_history[i]*denominator_polynomial[i+1];
  }

  // Sometimes useful for assessing stability
  //cout << "numerator_contribution " << numerator_result*polynomial_factor/denominator_polynomial[0] << " denominator_contribution " << -denominator_result/denominator_polynomial[0] << ")" << endl;
  double result = (numerator_result*polynomial_factor-denominator_result)/denominator_polynomial[0];

  // Rotate y(t-1) history
  output_history.push_front(result);
  output_history.pop_back();

//  cout << input_history[0] << " => " << output_history[0] << endl;

  return result;

}

void AutoStep::Instruments::BandPassButterworthFilter::Note::calculate_filter_polynomials() {

  // Find the butterworth poles
  std::vector<complex<double> > poles(order);
  for (int i=0;i<order;i++) {
    double arg = M_PI*(2*(i+1)+order-1)/(2*order);
    poles[i] = polar(1e0, arg);
    cout << "POLE: " << poles[i] << endl;
  }

  complex<double> foo = sqrt(complex<double>(-1e0));
  cout << "(i) foo = sqrt(-1) = " << foo << endl;
  cout << "(2i) (foo+1)^2 = " << (foo+polar(1e0, 0e0))*(foo+polar(1e0, 0e0)) << endl;

  // Pre warp the filter frequencies
  // We know centre_freq=w0 and band_width=w2-w1. w0^2 = w1*w2
  // w2 = bw+w1 ; w0^2 - w1bw - w1^2 = 0
  // w1 = w2-bw ; w0^2 + w2bw - w2^2 = 0
  // w1 < w0 ; w
  // w1 = (-bw/2 +- sqrt(1/4 bw^2 + w0^2))
  //    = w0(1-sqrt(5))/2 // Reject solution above w0
  // w2 = (bw/2 +- sqrt(1/4 bw^2 + w0^2))
  // Only use + part, because the -ve part will result in a negative frequency.
  //
  // Warp w1, warp w2, then compute w0' and bw' based on those values

  double ang_centre_freq = centre_freq*2e0*M_PI;
  double ang_band_width = band_width*2e0*M_PI;

  double w1w2_base = sqrt(2.5e-1*ang_band_width*ang_band_width+ang_centre_freq*ang_centre_freq);
  double w1 = w1w2_base-5e-1*ang_band_width;
  double w2 = w1w2_base+5e-1*ang_band_width;
  double pre_warped_w1 = bilinear_pre_warp(w1);
  double pre_warped_w2 = bilinear_pre_warp(w2);

  double pre_warped_w0 = sqrt(pre_warped_w1*pre_warped_w2);
  double pre_warped_Q = pre_warped_w0/(pre_warped_w2-pre_warped_w1);
  double wc = 1e0;

  cout << "T " << time_step << endl;
  cout << "bw " << ang_band_width << endl;
  cout << "w0 " << ang_centre_freq << endl;
  cout << "pre_warped_w1 " << pre_warped_w1 << endl;
  cout << "pre_warped_w2 " << pre_warped_w2 << endl;
  cout << "pre_warped_w0 " << pre_warped_w0 << endl;
  cout << "pre_warped_Q " << pre_warped_Q << endl;

  // Results
  double polynomial_factor = 1e0;
  Array1D<complex<double> > denominator_polynomial(1);
  Array1D<double> numerator_polynomial(1);

  denominator_polynomial[0] = 1e0;
  numerator_polynomial[0] = 1e0;

  // Build the denominator polynomial
  for (int i=0; i<order; i++) {

    complex<double> t1 = wc*pre_warped_Q*pre_warped_w0*(time_step*time_step)/4e0;
    complex<double> t2 = poles[i]*complex<double>(time_step/2e0);
    complex<double> t3 = wc*pre_warped_Q/pre_warped_w0;

    cout << "t1: " << t1 << endl;
    cout << "t2: " << t2 << endl;
    cout << "t3: " << t3 << endl;

    Array1D<complex<double> > polynomial_section(3);
    polynomial_section[0] = (t1-t2+t3);
    polynomial_section[1] = (2e0*t1 -2e0*t3);
    polynomial_section[2] = (t1+t2+t3);

    cout << "denominator section: " << polynomial_section << endl;

    double this_denom_magnitude = abs(polynomial_section[0]);

    polynomial_section[0] /= this_denom_magnitude;
    polynomial_section[1] /= this_denom_magnitude;
    polynomial_section[2] /= this_denom_magnitude;

    cout << "denominator section: " << polynomial_section << endl;

    polynomial_factor = polynomial_factor*time_step/(2e0*this_denom_magnitude);
    cout << "Convolution in progress between " << denominator_polynomial << " and " << polynomial_section << endl;
    denominator_polynomial = convolve(denominator_polynomial, polynomial_section);
    cout << "Result: " << denominator_polynomial << endl;

  }

  Array1D<double> real_denominator_polynomial(denominator_polynomial.dim1());

  for (int i=0; i<real_denominator_polynomial.dim1(); i++) {
    // Don't normalize this one - it's just (1 - z^-1)^n
    real_denominator_polynomial[i] = denominator_polynomial[i].real();
  }


  // Build the numerator polynomial
  for (int i=0; i<order; i++) {
    // Don't normalize this one - it's just (1 - z^-1)^n
    Array1D<double> polynomial_section(3);

    polynomial_section[0] = 1e0;
    polynomial_section[1] = 0e0;
    polynomial_section[2] = -1e0;

    numerator_polynomial = convolve(numerator_polynomial, polynomial_section);
  }

  cout << "Numerator: " << numerator_polynomial << endl;
  cout << "denominator: " << denominator_polynomial << endl;
  cout << "factor: " << polynomial_factor << endl;

  this->polynomial_factor = polynomial_factor;
  this->numerator_polynomial = numerator_polynomial;
  this->denominator_polynomial = real_denominator_polynomial;
  this->input_history.resize(numerator_polynomial.dim1(), 0e0);
  this->output_history.resize(real_denominator_polynomial.dim1(), 0e0);

  return;

}

