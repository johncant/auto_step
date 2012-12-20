#ifndef __BAR_SIMPLE_LINE_H__
#define __BAR_SIMPLE_LINE_H__

#include <tnt/tnt.h>
#include "haar.h"

namespace AutoStep {
  class BarSimpleLine {
    // 1 Bar's worth of musical line (melody or harmony)

    public:
    
    TNT::Array2D<double> wavelet_amplitudes;

    BarSimpleLine();
    void random_initialize();
    double evaluate_at(double t);
  };
}

#endif
