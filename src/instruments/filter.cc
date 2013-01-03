#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <iostream>
#include "filter.h"


AutoStep::Instruments::Filter::Sound::Sound(const boost::intrusive_ptr<AutoStep::Sound> &_input) : input(_input) {
}


// Delay - 0 samples = causality
double AutoStep::Instruments::Filter::Sound::delay() {
  return input->delay();
}

double AutoStep::Instruments::Filter::Sound::duration(void) {
  return input->duration();
}

double AutoStep::Instruments::Filter::Sound::start_time(void) {
  return input->start_time();
}


