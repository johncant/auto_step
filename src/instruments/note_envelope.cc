#include "note_envelope.h"
#include <math.h>
#include "config.h"

// Give start as the absolute time. Give every other time relative to the start time. The time constants are exponential time constants. The amplitudes are linear and absolute.
AutoStep::Instruments::NoteEnvelope::Sound::Sound (double _start, double _attack_time_const, double _attack_amplitude, double _decay_time_const, double _sustain_amplitude, double _release_start_time, double _release_time_const) : start(_start), attack_time_const(_attack_time_const), attack_amplitude(_attack_amplitude), decay_time_const(_decay_time_const), sustain_amplitude(_sustain_amplitude), release_start_time(_release_start_time) {
}


// These are required to control of the envelope - i.e. when the sound should be played

// The peak of the attack will be played at the start time. The attack gets played anti-causally.
double AutoStep::Instruments::NoteEnvelope::Sound::delay() {
  return attack_time_const*log(AutoStep::Config::max_integer_amplitude);
}

double AutoStep::Instruments::NoteEnvelope::Sound::start_time() {
  return start;
}

// Total duration actually = delay+duration
double AutoStep::Instruments::NoteEnvelope::Sound::duration() {
  return release_start_time+release_time_const*log(AutoStep::Config::max_integer_amplitude);
}


// The actual envelope
double AutoStep::Instruments::NoteEnvelope::Sound::output(double time) {

  // attack_amplitude * exponential_growth (t - start)

  if (time < start) {
    // Attack phase
    return attack_amplitude*exp((time - start)/attack_time_const);
  } else if (time <= start+release_start_time) {
    // The decay and sustain phase
    return sustain_amplitude+(attack_amplitude-sustain_amplitude)*exp((start - time)/decay_time_const);
  } else {
    // The release phase
    // Find the amplitude at the end of the sustain phase. This gets rid of any step at the start of the release phase.
    double release_amplitude = (attack_amplitude-sustain_amplitude)*exp(-release_start_time/decay_time_const); // TODO - cache this.
    return release_amplitude * exp((start+release_start_time-time)/release_time_const);
  }

}



