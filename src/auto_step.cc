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

// pulse
#include <pulse/error.h>
#include <pulse/simple.h>

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

using namespace std;
using namespace TNT;


void fail_with_pa_error(int error) {
  fprintf(stderr, __FILE__":%s\n", pa_strerror(error));
  exit(0);
}


int main(void) {

  srand ( time(NULL) );

  pa_simple *s;
  pa_sample_spec ss;

  ss.format = PA_SAMPLE_S16NE; //Signed 16 Bit PCM, native endian.
  ss.channels = 2;
  ss.rate = 44100;
  int error=0;
  int wave_max = 32767;


  s = pa_simple_new(NULL,               // Use the default server.
                   "Dubstep generator",           // Our application's name.
                   PA_STREAM_PLAYBACK,
                   NULL,               // Use the default device.
                   "Music",            // Description of our stream.
                   &ss,                // Our sample format.
                   NULL,               // Use default channel map
                   NULL,               // Use default buffering attributes.
                   &error               // Ignore error code.
                   );



  if (error) fail_with_pa_error(error);

  pa_usec_t lat = pa_simple_get_latency(s, &error);
  if (error) fail_with_pa_error(error);

  printf("Latency: %lu usec\n", lat);


  // Dump a sine wave @ 440 Hz

  // Choose the signal length

  AutoStep::BarSimpleLine bar;
  double beat_freq = 0.25; // 60bpm

  double signal_length = 5; // seconds
  int samples_count = (int) double(signal_length)*int(ss.rate);
  int16_t data[samples_count];

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
  boost::intrusive_ptr<AutoStep::Sound> dubstep_sound = dubstep_instrument.output(sq_wave_sound, base_freq, 1e0*base_freq, 2, 1/double(ss.rate));

  for (int i=0; i<samples_count; i++) {

    time = double(i)/double(ss.rate);

//    double sound = bar.evaluate_at(fmod(time*beat_freq, 1));
//    double freq = base_freq*pow(2, sound/12);
    //cout << sound;
    //cout << freq;
//    double val = amplitude*(dubstep_sound->output(time))*(womp->output(time)); //*sin(2*pi*modulation_freq*time);
    double val = amplitude*(sawtooth_sound->output(time)); //*(womp->output(time)); //*sin(2*pi*modulation_freq*time);

    if (val > 1e0) {
      cout << "Sound value has gone above maximum - " << val << endl;
    }

    data[i] = (int16_t) double(wave_max)*val;
    //data[i] = (int16_t) double(wave_max)*amplitude*(0.5*sound0.output(time)+0.5*sound1.output(time)); //*sin(2*pi*modulation_freq*time);

  }

  pa_simple_write(s, &data, samples_count, &error);

  for (int i=0; i<samples_count; i++) {

    time = double(i)/double(ss.rate);

//    double sound = bar.evaluate_at(fmod(time*beat_freq, 1));
//    double freq = base_freq*pow(2, sound/12);
    //cout << sound;
    //cout << freq;
//    double val = amplitude*(dubstep_sound->output(time))*(womp->output(time)); //*sin(2*pi*modulation_freq*time);
    double val = amplitude*(dubstep_sound->output(time))*(womp0->output(time))*womp1->output(time); //*sin(2*pi*modulation_freq*time);

    if (val > 1e0) {
      cout << "Sound value has gone above maximum - " << val << endl;
    }

    data[i] = (int16_t) double(wave_max)*val;
    //data[i] = (int16_t) double(wave_max)*amplitude*(0.5*sound0.output(time)+0.5*sound1.output(time)); //*sin(2*pi*modulation_freq*time);

  }

  pa_simple_write(s, &data, samples_count, &error);

  if (error) {
    printf("Bombing out after %d iterations.\n", 1);
    fail_with_pa_error(error);
  }


  printf("Wrote %d samples!\n", samples_count);
  pa_simple_free(s);

  return 0;

}
