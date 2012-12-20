#ifndef __SINE_WAVE_H__
#define __SINE_WAVE_H__

#include "../instrument.h"
#include "../note.h"


namespace AutoStep {
  namespace Instruments {
    class SineWave : public AutoStep::Instrument {
      public:
      class Note : public AutoStep::Note {
        friend class SineWave;
        Note(double _freq);
        private:
        double freq;

        public:
        double output(double time);
      };

      boost::intrusive_ptr<SineWave::Note> output(double freq);
    };
  }
}

#endif
