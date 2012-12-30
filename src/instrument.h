#ifndef __INSTRUMENT_H__
#define __INSTRUMENT_H__

#include "note.h"
#include <boost/smart_ptr/intrusive_ptr.hpp>

// An instrument is an object which produces notes for a given frequency.
namespace AutoStep {
  class Instrument {
    boost::intrusive_ptr<Note> output();
  };
}

#endif
