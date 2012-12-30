#ifndef __FILTER_H__
#define __FILTER_H__

#include "../instrument.h"
#include "../note.h"

// ABC for filter
namespace AutoStep {
  namespace Instruments {
    class Filter : public AutoStep::Instrument {
      public:
      class Note : public AutoStep::Note {
        friend class Filter;
        public:
        boost::intrusive_ptr<AutoStep::Note> input;
        Note(const boost::intrusive_ptr<AutoStep::Note> &_input);
        Note(const AutoStep::Note &_input);
      };

      int delay(); // Allows finite impulse pre-response anti-causal filters
    };
  }
}

#endif
