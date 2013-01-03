#ifndef __BAND_PASS_BUTTERWORTH_FILTER_H__
#define __BAND_PASS_BUTTERWORTH_FILTER_H__

#include "../filter.h"
#include <tnt/tnt.h>
#include <deque>

namespace AutoStep {
  namespace Instruments {
    class BandPassButterworthFilter : public AutoStep::Instruments::Filter {
      public:
      class Sound : public AutoStep::Instruments::Filter::Sound {
        friend class BandPassButterworthFilter;
        protected:
        // Characteristics which define the filter
        double centre_freq;
        double band_width;
        unsigned int order;

        // The filter itself
        std::vector<double> filter_conv;
        TNT::Array1D<double> numerator_polynomial;
        TNT::Array1D<double> denominator_polynomial;
        double polynomial_factor;
        std::deque<double> input_history;
        std::deque<double> output_history;

        // The input sound is defined in the superclass
        double bilinear_pre_warp(double input);
        double output(double time);
        void calculate_filter_polynomials();
        Sound(boost::intrusive_ptr<AutoStep::Sound> &_input, double _centre_freq, double _bandwidth, unsigned int _order);
      };

      boost::intrusive_ptr<AutoStep::Sound> output(boost::intrusive_ptr<AutoStep::Sound> &_input, double centre_freq, double bandwidth, unsigned int order);
    };
  }
}

#endif
