#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "sine_wave.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../haar.h"

boost::intrusive_ptr<AutoStep::Instruments::SineWave::Note> AutoStep::Instruments::SineWave::output(double freq) {
  return boost::intrusive_ptr<AutoStep::Instruments::SineWave::Note>(new AutoStep::Instruments::SineWave::Note(freq));
}

AutoStep::Instruments::SineWave::Note::Note(double _freq) : freq(_freq) {}

double AutoStep::Instruments::SineWave::Note::output(double time) {
  return sin(2*M_PI*freq*time);
}

