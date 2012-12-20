#ifndef __TNT_EXT_H__
#define __TNT_EXT_H__

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <tnt/tnt.h>

namespace TNT {
  template <class T> 
  TNT::Array2D<T> transpose(const TNT::Array2D<T> input) {
    Array2D<T> result(input.dim2(), input.dim1());

    for(unsigned int i=0; i<input.dim1(); i++) {
      for(unsigned int j=0; j<input.dim2(); j++) {
        result[j][i] = input[i][j];
      }
    }

    return result;

  }
}

#endif
