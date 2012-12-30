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
      };

      boost::intrusive_ptr<SawTooth::Sound> output(double freq);
    };
  }
}

#endif
