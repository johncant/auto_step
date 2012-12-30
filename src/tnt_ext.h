#ifndef __TNT_EXT_H__
#define __TNT_EXT_H__

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <tnt/tnt.h>

namespace TNT {

  // Transpose
  template <class T> 
  TNT::Array2D<T> transpose(const TNT::Array2D<T> &input) {
    Array2D<T> result(input.dim2(), input.dim1());

    for(unsigned int i=0; i<input.dim1(); i++) {
      for(unsigned int j=0; j<input.dim2(); j++) {
        result[j][i] = input[i][j];
      }
    }

    return result;

  }

  // 1D Convolution
  template <class T>
  TNT::Array1D<T> convolve(const TNT::Array1D<T> &input0, const TNT::Array1D<T> &input1) {
    TNT::Array1D<T> result(input0.dim1()+input1.dim1()-1, 0e0);
    for (int i=0; i<input0.dim1(); i++) {
      for (int j=0; j<input1.dim1(); j++) {
        result[i+j] += input0[i] * input1[j];
      }
    }

    return result;
  }

  template <class T>
  TNT::Array1D<T> convolve(const TNT::Array1D<T> &input0, const TNT::Array2D<T> &input1) {
    std::cerr << "Not yet implemented" << std::endl;
  }

  template <class T>
  TNT::Array2D<T> convolve(const TNT::Array2D<T> &input0, const TNT::Array1D<T> &input1) {
    std::cerr << "Not yet implemented" << std::endl;
  }

  template <class T>
  TNT::Array2D<T> convolve(const TNT::Array2D<T> &input0, const TNT::Array2D<T> &input1) {
    std::cerr << "Not yet implemented" << std::endl;
  }

}

#endif
