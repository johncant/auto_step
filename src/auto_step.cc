#if HAVE_CONFIG_H
# include <config.h>
#endif

// std libs
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// pulse
#include <pulse/error.h>
#include <pulse/simple.h>

void fail_with_pa_error(int error) {
  fprintf(stderr, __FILE__":%s\n", pa_strerror(error));
  exit(0);
}

int main(void) {

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
  double signal_length = 2; // seconds
  int samples_count = int(signal_length)*int(ss.rate);
  int16_t data[samples_count];

  const double pi = 3.14159265898;
  double freq = 440; // Hz
  double amplitude = 1; // 0-1
  double time = 0;

  for (int i=0; i<samples_count; i++) {

    time = double(i)/double(ss.rate);
    data[i] = (int16_t) double(wave_max)*amplitude*sin(2*pi*freq*time);

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
