#include "haar.h"
#include "tnt_ext.h"
#include <iostream>


using namespace TNT;
using namespace std;



std::map<unsigned int, TNT::Array2D<double> > AutoStep::Haar::MatrixCache::stash;

double AutoStep::Haar::mother(double t) {
  if (t < 0 || t >= 1) {
    return 0;
  } else if (t < 0.5) {
    return 1;
  } else {
    return -1;
  }
}

Array2D<double>& AutoStep::Haar::MatrixCache::compute(unsigned int size) {
  Array2D<double> haar(size, size); // All elements 0
  // size must be a power of 2
  // Do the computation:

  // Sparsley.
  for (unsigned int hl=1, wl;hl <= size;hl=wl) {
    wl = 2*hl; //wavelength
    // n = Number of elements taken up by half of the wavelet(for 8*8 this would be 1, 2, 4, 8)

    // Move along in leaps of 2hl. We get n:i => 1:0 1:2 1:4 1:6 2:0 2:4 4:0 8:0
    for (unsigned int start=0; start<size; start+=wl) {

      // Integer division to get the row
      int row = (size/wl) + (start/wl);

      // Fill in all the 1s.
      for (unsigned int i=start ; i < start+hl; i++) haar[row][i] = 1;

      // Fill in all the -1s. The extra condition prevents us from spilling out of the matrix in row 0
      for (unsigned int i=start+hl ; i < start+wl && i < size; i++) haar[row][i] = -1;
    }
  }

  // This might cause a segfault or memory leak :| - eek!

  cout << "Haar matrix for size " << size << endl;
  cout << haar << endl;

  stash[size] = haar;
  return stash[size];

}

Array2D<double>& AutoStep::Haar::MatrixCache::get(unsigned int size) {
  if (stash.count(size)) {
    return stash[size];
  } else {
    return compute(size);
  }
}


// Most inefficient ever. I want to only multiply a row but too tired.
double AutoStep::Haar::evaluate(double t, TNT::Array2D<double> transform) {
  int transform_length = transform.dim1();
  TNT::Array2D<double> inverse_haar_matrix = TNT::transpose(MatrixCache::get(transform_length));
  TNT::Array2D<double> result(transform_length, 1);

  result = matmult(inverse_haar_matrix, transform);
  int index = int(t*double(transform_length));
  if (index >= 0 && index < transform_length) {
    return result[index][0];
  } else {
    cerr << "index:" << index << " Time " << t << " is not between 0 and 1" << endl;
  }
}

