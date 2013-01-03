#ifndef __NOTE_ENVELOPE_H__
#define __NOTE_ENVELOPE_H__

#include "../instrument.h"
#include "../sound.h"

// ABC for filter
namespace AutoStep {
  namespace Instruments {
    class NoteEnvelope {
      public:
      class Sound : public AutoStep::Sound {
        public:
        Sound(double start, double attack_time_const, double attack_amplitude, double decay_time_const, double sustain_amplitude, double release_start_time, double release_time_const);

        double start;
        double attack_time_const;     // Exponential time constant for attack phase
        double attack_amplitude;      // Maximum attack envelope amplitude
        double decay_time_const;      // Exponential time constant for decay phase
        double sustain_amplitude;     // Sustain phase assumed to be constant volume
        double release_start_time;    // Time after end of note at which start of release will occur
        double release_time_const;    // Exponential time constant for release phase

        double delay(); // This is anti-causal if we time the attack to peak at the note start time
        double start_time();
        double duration();

        double output(double time);
      };

      double output(double start, double attack_time_const, double attack_amplitude, double decay_time_const, double sustain_amplitude, double release_start_time, double release_time_const);
    };
  }
}

#endif
