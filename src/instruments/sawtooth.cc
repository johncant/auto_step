#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "sawtooth.h"
#include "../haar.h"
#include <math.h>

boost::intrusive_ptr<AutoStep::Instruments::SawTooth::Note> AutoStep::Instruments::SawTooth::output(double freq) {
  return boost::intrusive_ptr<AutoStep::Instruments::SawTooth::Note>(new AutoStep::Instruments::SawTooth::Note(freq));
}

AutoStep::Instruments::SawTooth::Note::Note(double _freq) : freq(_freq) {}

double AutoStep::Instruments::SawTooth::Note::output(double time) {
  return fmod(time, freq);
}

