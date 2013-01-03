#ifndef __MODULATOR_H__
#define __MODULATOR_H__

#include "../../sound.h"
#include "../filter.h"
#include <boost/smart_ptr/intrusive_ptr.hpp>

namespace AutoStep {
  namespace Instruments {

    class Modulator : public AutoStep::Instruments::Filter {
      public:
      class Sound : public AutoStep::Instruments::Filter::Sound {
        public:
        boost::intrusive_ptr<AutoStep::Sound> modulation;
        double output(double time);
        double delay();
        Sound(boost::intrusive_ptr<AutoStep::Sound> input, boost::intrusive_ptr<AutoStep::Sound> modulation);
        double duration();
      };

      boost::intrusive_ptr<AutoStep::Sound> output(boost::intrusive_ptr<AutoStep::Sound> input, boost::intrusive_ptr<AutoStep::Sound> modulation);
    };

  }
}

#endif
