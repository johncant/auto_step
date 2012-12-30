#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <iostream>
#include "filter.h"


AutoStep::Instruments::Filter::Sound::Sound(const boost::intrusive_ptr<AutoStep::Sound> &_input) : input(_input) {
}


// Delay - assume 0 samples
int AutoStep::Instruments::Filter::delay() {
  return 0;
}
