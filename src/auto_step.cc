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

  double signal_length = 25; // seconds
  int samples_count = int(signal_length)*int(ss.rate);
  int16_t data[samples_count];

  const double pi = 3.14159265898;
  double base_freq = 55; // Hz
  double amplitude = 1; // 0-1
  double time = 0; // Seconds

  double modulation_freq = 11; // Hz

//  AutoStep::Instruments::SineWave instrument0;
//  AutoStep::Instruments::SineWave::Note note0 = instrument0.output(base_freq);

  AutoStep::Instruments::SquareWave instrument1;
  boost::intrusive_ptr<AutoStep::Note> note1 = instrument1.output(base_freq);


  for (int i=0; i<samples_count; i++) {

    
    time = double(i)/double(ss.rate);

//    double note = bar.evaluate_at(fmod(time*beat_freq, 1));
//    double freq = base_freq*pow(2, note/12);
    //cout << note;
    //cout << freq;
    data[i] = (int16_t) double(wave_max)*amplitude*(note1->output(time)); //*sin(2*pi*modulation_freq*time);
    //data[i] = (int16_t) double(wave_max)*amplitude*(0.5*note0.output(time)+0.5*note1.output(time)); //*sin(2*pi*modulation_freq*time);

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
