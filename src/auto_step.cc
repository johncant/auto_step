#if HAVE_CONFIG_H
# include <config.h>
#endif

// std libs
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

// C++
#include <vector>
#include <iostream>
#include <map>


// Maths
#include <tnt/tnt.h>

// AutoStep
#include "haar.h"
#include "config.h"
#include "tnt_ext.h"
#include "bar_simple_line.h"

// Instruments
#include "instruments/square_wave.h"
#include "instruments/sine_wave.h"
#include "instruments/filters/band_pass_butterworth.h"

// Player
#include "player.h"
#include <unistd.h>

using namespace std;
using namespace TNT;




int main(int argc, char** argv) {

  srand ( time(NULL) );

  // Choose the signal length

  AutoStep::BarSimpleLine bar;
  double beat_freq = 0.25; // 60bpm

  double signal_length = 5; // seconds

  const double pi = 3.14159265898;
  double base_freq = 55; // Hz
  double amplitude = 0.2; // 0-1
  double time = 0; // Seconds

  double modulation_freq = 22.5; // Hz
  double womp_freq = 1;

  AutoStep::Instruments::SineWave instrument0;
  boost::intrusive_ptr<AutoStep::Sound> womp0 = instrument0.output(modulation_freq);
  boost::intrusive_ptr<AutoStep::Sound> womp1 = instrument0.output(womp_freq);

  AutoStep::Instruments::SineWave sine_wave_generator;
  boost::intrusive_ptr<AutoStep::Sound> sine_wave_sound = sine_wave_generator.output(base_freq);

  AutoStep::Instruments::SquareWave sawtooth_generator;
  boost::intrusive_ptr<AutoStep::Sound> sawtooth_sound = sawtooth_generator.output(base_freq);

  AutoStep::Instruments::SquareWave sq_wave_generator;
  boost::intrusive_ptr<AutoStep::Sound> sq_wave_sound = sq_wave_generator.output(base_freq);

  AutoStep::Instruments::BandPassButterworthFilter dubstep_instrument;
  boost::intrusive_ptr<AutoStep::Sound> dubstep_sound = dubstep_instrument.output(sq_wave_sound, base_freq, 1e0*base_freq, 2);

  AutoStep::Player player(sq_wave_sound);

  player.start();

  sleep(2);

  player.stop();

  return 0;

}
