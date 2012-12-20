#ifndef __HAAR_H__
#define __HAAR_H__

#include <tnt/tnt.h>
#include <map>

namespace AutoStep {


  namespace Haar {

    // The mother wavelet function
    double mother(double t);

    // Cache of Haar matrices (not normalized)
    class MatrixCache {

      private:
      static std::map<unsigned int, TNT::Array2D<double> > stash;
      static TNT::Array2D<double>& compute(unsigned int size);

      public:
      static TNT::Array2D<double>& get(unsigned int size);

    };

    // Most inefficient ever. I want to only multiply a row but too tired.
    // Evaluate the waveform at time t
    double evaluate(double t, TNT::Array2D<double> transform);

  }

}

#endif
