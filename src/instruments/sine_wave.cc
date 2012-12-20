#include "sine_wave.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../haar.h"

AutoStep::Instruments::SineWave::Note AutoStep::Instruments::SineWave::output(double freq) {
  return AutoStep::Instruments::SineWave::Note(freq);
}

AutoStep::Instruments::SineWave::Note::Note(double _freq) : freq(_freq) {}

double AutoStep::Instruments::SineWave::Note::output(double time) {
  return sin(2*M_PI*freq*time);
}

