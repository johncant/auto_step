#include "modulator.h"
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

double AutoStep::Instruments::Modulator::Sound::output(const double time) {
  return input->output(time)*modulation->output(time);
}

double AutoStep::Instruments::Modulator::Sound::delay() {
  return std::max(input->delay(), modulation->delay());
}

AutoStep::Instruments::Modulator::Sound::Sound(const boost::intrusive_ptr<AutoStep::Sound> input, const boost::intrusive_ptr<AutoStep::Sound> modulation) : AutoStep::Instruments::Filter::Sound(input) {}

boost::intrusive_ptr<AutoStep::Sound> output(const boost::intrusive_ptr<AutoStep::Sound> input, const boost::intrusive_ptr<AutoStep::Sound> modulation) {
  return boost::intrusive_ptr<AutoStep::Sound>(new AutoStep::Instruments::Modulator::Sound(input, modulation));
}

double AutoStep::Instruments::Modulator::Sound::duration() {
  if (isinf(input->duration())) {
    return modulation->duration();
  } else {
    if (isinf(modulation->duration())) {
      return input->duration();
    } else {
      std::cerr << "TODO: Find duration of modulation between two finite-length signals" << endl;
      return 0e0;
    }
  }
}
