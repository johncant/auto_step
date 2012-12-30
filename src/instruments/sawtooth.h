#ifndef __SAWTOOTH_H__
#define __SAWTOOTH_H__

#include "../instrument.h"
#include "../note.h"


namespace AutoStep {
  namespace Instruments {
    class SawTooth : public AutoStep::Instrument {
      public:
      class Note : public AutoStep::Note {
        friend class SawTooth;
        private:
        Note(double _freq);
        double freq;

        public:
        double output(double time);
      };

      boost::intrusive_ptr<SawTooth::Note> output(double freq);
    };
  }
}

#endif
