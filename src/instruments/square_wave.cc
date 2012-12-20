#include "square_wave.h"
#include "../haar.h"

AutoStep::Instruments::SquareWave::Note AutoStep::Instruments::SquareWave::output(double freq) {
  return AutoStep::Instruments::SquareWave::Note(freq);
}

AutoStep::Instruments::SquareWave::Note::Note(double _freq) : freq(_freq) {}
double AutoStep::Instruments::SquareWave::Note::output(double time) {
  return AutoStep::Haar::mother(fmod(freq*time, 1));
}

