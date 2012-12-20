#ifndef __INSTRUMENT_H__
#define __INSTRUMENT_H__

#include "note.h"

// An instrument is an object which produces notes for a given frequency.
namespace AutoStep {
  class Instrument {
    Note output(double freq);
  };
}

#endif
