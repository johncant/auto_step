#ifndef __INSTRUMENT_H__
#define __INSTRUMENT_H__

#include "sound.h"
#include <boost/smart_ptr/intrusive_ptr.hpp>

// An instrument is an object which produces sounds for a given frequency.
namespace AutoStep {
  class Instrument {
    boost::intrusive_ptr<Sound> output();
  };
}

#endif
