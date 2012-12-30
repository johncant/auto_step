#ifndef __SQUARE_WAVE_H__
#define __SQUARE_WAVE_H__

#include "../instrument.h"
#include "../sound.h"


namespace AutoStep {
  namespace Instruments {
    class SquareWave : public AutoStep::Instrument {
      public:
      class Sound : public AutoStep::Sound {
        friend class SquareWave;
        private:
        Sound(double _freq);
        double freq;

        public:
        double output(double time);
      };

      boost::intrusive_ptr<SquareWave::Sound> output(double freq);
    };
  }
}

#endif
