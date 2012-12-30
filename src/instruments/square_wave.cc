#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "square_wave.h"
#include "../haar.h"

boost::intrusive_ptr<AutoStep::Instruments::SquareWave::Sound> AutoStep::Instruments::SquareWave::output(double freq) {
  return boost::intrusive_ptr<AutoStep::Instruments::SquareWave::Sound>(new AutoStep::Instruments::SquareWave::Sound(freq));
}

AutoStep::Instruments::SquareWave::Sound::Sound(double _freq) : freq(_freq) {}

double AutoStep::Instruments::SquareWave::Sound::output(double time) {
  return AutoStep::Haar::mother(fmod(freq*time, 1));
}

