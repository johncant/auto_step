#ifndef __SAWTOOTH_H__
#define __SAWTOOTH_H__

#include "../instrument.h"
#include "../sound.h"


namespace AutoStep {
  namespace Instruments {
    class SawTooth : public AutoStep::Instrument {
      public:
      class Sound : public AutoStep::Sound {
        friend class SawTooth;
        private:
        Sound(double _freq);
        double freq;

        public:
        double output(double time);

        double delay(void);
        double duration(void);
        double start_time(void);

      };

      boost::intrusive_ptr<SawTooth::Sound> output(double freq);
    };
  }
}

#endif
