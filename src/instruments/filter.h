#ifndef __FILTER_H__
#define __FILTER_H__

#include "../instrument.h"
#include "../sound.h"

// ABC for filter
namespace AutoStep {
  namespace Instruments {
    class Filter : public AutoStep::Instrument {
      public:
      class Sound : public AutoStep::Sound {
        friend class Filter;
        public:
        boost::intrusive_ptr<AutoStep::Sound> input;
        Sound(const boost::intrusive_ptr<AutoStep::Sound> &_input);
        Sound(const AutoStep::Sound &_input);
      };

      int delay(); // Allows finite impulse pre-response anti-causal filters
    };
  }
}

#endif
