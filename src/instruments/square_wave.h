#ifndef __SQUARE_WAVE_H__
#define __SQUARE_WAVE_H__

#include "../instrument.h"
#include "../note.h"


namespace AutoStep {
  namespace Instruments {
    class SquareWave : public AutoStep::Instrument {
      public:
      class Note : public AutoStep::Note {
        friend class SquareWave;
        private:
        Note(double _freq);
        double freq;

        public:
        double output(double time);
      };

      boost::intrusive_ptr<SquareWave::Note> output(double freq);
    };
  }
}

#endif
