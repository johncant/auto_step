#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "sawtooth.h"
#include "../haar.h"
#include <math.h>
#include <limits>

boost::intrusive_ptr<AutoStep::Instruments::SawTooth::Sound> AutoStep::Instruments::SawTooth::output(double freq) {
  return boost::intrusive_ptr<AutoStep::Instruments::SawTooth::Sound>(new AutoStep::Instruments::SawTooth::Sound(freq));
}

AutoStep::Instruments::SawTooth::Sound::Sound(double _freq) : freq(_freq) {}

double AutoStep::Instruments::SawTooth::Sound::output(double time) {
  return fmod(time, freq);
}

double AutoStep::Instruments::SawTooth::Sound::duration(void) {
  return std::numeric_limits<double>::infinity();
}

double AutoStep::Instruments::SawTooth::Sound::delay(void) {
  return 0;
}

double AutoStep::Instruments::SawTooth::Sound::start_time(void) {
  return 0;
}
