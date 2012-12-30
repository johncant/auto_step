#ifndef __BAND_PASS_BUTTERWORTH_FILTER_H__
#define __BAND_PASS_BUTTERWORTH_FILTER_H__

#include "../filter.h"
#include <tnt/tnt.h>
#include <deque>

namespace AutoStep {
  namespace Instruments {
    class BandPassButterworthFilter : public AutoStep::Instruments::Filter {
      public:
      class Note : public AutoStep::Instruments::Filter::Note {
        friend class BandPassButterworthFilter;
        protected:
        // Characteristics which define the filter
        double centre_freq;
        double band_width;
        unsigned int order;
        double time_step;

        // The filter itself
        std::vector<double> filter_conv;
        TNT::Array1D<double> numerator_polynomial;
        TNT::Array1D<double> denominator_polynomial;
        double polynomial_factor;
        std::deque<double> input_history;
        std::deque<double> output_history;

        // The input note is defined in the superclass
        double bilinear_pre_warp(double input);
        double output(double time);
        void calculate_filter_polynomials();
        int delay(); // Allows anti-causal filters
        Note(boost::intrusive_ptr<AutoStep::Note> &_input, double _centre_freq, double _bandwidth, unsigned int _order, double _time_step);
      };

      boost::intrusive_ptr<AutoStep::Note> output(boost::intrusive_ptr<AutoStep::Note> &_input, double centre_freq, double bandwidth, unsigned int order, double time_step);
      double time_step;
    };
  }
}

#endif
