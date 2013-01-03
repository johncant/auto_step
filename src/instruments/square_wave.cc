#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "square_wave.h"
#include <limits>
#include "../haar.h"

boost::intrusive_ptr<AutoStep::Instruments::SquareWave::Sound> AutoStep::Instruments::SquareWave::output(double freq) {
  return boost::intrusive_ptr<AutoStep::Instruments::SquareWave::Sound>(new AutoStep::Instruments::SquareWave::Sound(freq));
}

AutoStep::Instruments::SquareWave::Sound::Sound(double _freq) : freq(_freq) {}

double AutoStep::Instruments::SquareWave::Sound::output(double time) {
  return AutoStep::Haar::mother(fmod(freq*time, 1));
}

double AutoStep::Instruments::SquareWave::Sound::duration(void) {
  return std::numeric_limits<double>::infinity();
}

double AutoStep::Instruments::SquareWave::Sound::delay(void) {
  return 0;
}

double AutoStep::Instruments::SquareWave::Sound::start_time(void) {
  return 0;
}
