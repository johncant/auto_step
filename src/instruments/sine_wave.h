#ifndef __SINE_WAVE_H__
#define __SINE_WAVE_H__

#include "../instrument.h"
#include "../sound.h"


namespace AutoStep {
  namespace Instruments {
    class SineWave : public AutoStep::Instrument {
      public:
      class Sound : public AutoStep::Sound {
        friend class SineWave;
        Sound(double _freq);
        private:
        double freq;

        public:
        double output(double time);
        double delay(void);
        double duration(void);
        double start_time(void);
      };

      boost::intrusive_ptr<SineWave::Sound> output(double freq);
    };
  }
}

#endif
