#include "bar_simple_line.h"
#include "haar.h"

using namespace std;
using namespace TNT;

AutoStep::BarSimpleLine::BarSimpleLine() {
  wavelet_amplitudes = Array2D<double>(8, 1);
  random_initialize();
  cout << wavelet_amplitudes << endl;
}

void AutoStep::BarSimpleLine::random_initialize() {
  wavelet_amplitudes[0][0] = 0;
  for(int i=1; i< wavelet_amplitudes.dim1(); i++) {
    int variation = 2;
    wavelet_amplitudes[i][0] = (rand() % (2*variation+1)) - variation;
  }
}

double AutoStep::BarSimpleLine::evaluate_at(double t) {
  // t is between 0 and 1
  // return an answer which will be the number of semitones different from A
  return AutoStep::Haar::evaluate(t, wavelet_amplitudes);

}


