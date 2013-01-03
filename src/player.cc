#include "player.h"
#include "config.h"
#include <iostream>

// This class plays a sound from start to finish. The sound would typically be an instance of AutoStep::Instruments::Mixer::Sound

using namespace std;

void fail_with_pa_error(int error, const char* file, const int line) {
  cerr << "ERROR: " << file << ":" << line << ": " << pa_strerror(error) << endl;
  cout << "Fail" << endl;
  exit(0);
}


extern "C" {

  void write_cb (pa_stream* playback_stream, size_t nbytes, void* user_data) {
    ((AutoStep::Player*) user_data)->write_to_pulseaudio(nbytes);
  }

  void context_state_cb(pa_context* c, void* user_data) {

    if (pa_context_get_state(c) == PA_CONTEXT_READY) ((AutoStep::Player*) user_data)->context_ready();

  }

}


void AutoStep::Player::context_ready() {

    int error;

    pa_sample_spec ss;

    ss.format = PA_SAMPLE_S16NE; //Signed 16 Bit PCM, native endian.
    ss.channels = 1;
    ss.rate = AutoStep::Config::rate;


    playback_stream = pa_stream_new(pa_context_inst, "Playback stream", &ss, NULL);
    cout << "stream: " << playback_stream << endl;

    error = pa_stream_connect_playback(playback_stream, NULL, NULL, (pa_stream_flags_t) 0, NULL, NULL);
    if (error) fail_with_pa_error(error, __FILE__, __LINE__);


    int negative=0;
    pa_usec_t lat;

    error = pa_stream_get_latency(playback_stream, &lat, &negative);

    pa_stream_set_write_callback(playback_stream, write_cb, this);
    //cout << "Playback latency: " << lat << " usec" << endl;
    //if (error) fail_with_pa_error(error, __FILE__, __LINE__);

    pa_stream_cork(playback_stream, 0, NULL, NULL);
    cout << "Triggering playback " << pa_stream_trigger(playback_stream, NULL, this) << endl;

}


void AutoStep::Player::write_to_pulseaudio(size_t nbytes) {

  int error=0;

  int16_t* data = 0;
  size_t batch_length;

  cout << "Told to write " << nbytes << endl;

  cout << "Stream state: " << pa_stream_get_state(playback_stream) << endl;
  error = pa_stream_begin_write(playback_stream, (void**) &data, &nbytes);
  if (error) fail_with_pa_error(error, __FILE__, __LINE__);

  batch_length = nbytes/sizeof(int16_t);

  cout << "Allowed to write " << batch_length << " to buffer @ " << data << endl;

  for (int i=0; i<batch_length; i++) {
    player_current_time += AutoStep::Config::time_step;

    double val = AutoStep::Config::max_integer_amplitude*root_sound->output(player_current_time);
//      cout << player_current_time << " : " << val << endl;

    data[i] = (int16_t) val;
  }

//  cout << "Calling pa_write_stream with "
  error = pa_stream_write(playback_stream, data, nbytes, NULL, 0, PA_SEEK_RELATIVE);
  if (error) fail_with_pa_error(error, __FILE__, __LINE__);

  if (player_current_time > (root_sound->start_time()+root_sound->duration())) {
    cout << "Reached end of sound" << endl;
    stop();
  }

}

double AutoStep::Player::current_time() {
  return player_current_time;
}


AutoStep::Player::~Player() {
  pa_stream_disconnect(playback_stream);
  pa_stream_unref(playback_stream);
  pa_context_disconnect(pa_context_inst);
  pa_context_unref(pa_context_inst);
  pa_threaded_mainloop_stop(pa_threaded_mainloop_inst);
  pa_threaded_mainloop_free(pa_threaded_mainloop_inst);
}

AutoStep::Player::Player(const boost::intrusive_ptr<AutoStep::Sound> _root_sound) : root_sound(_root_sound) {

  player_current_time = -root_sound->delay();


  int error=0;
  pa_threaded_mainloop_inst = pa_threaded_mainloop_new();
  pa_threaded_mainloop_start(pa_threaded_mainloop_inst);

//  pa_signal_init(pa_threaded_mainloop_get_api(pa_threaded_mainloop_inst));

  cout << "threaded_mainloop: " << pa_threaded_mainloop_inst << endl;
  pa_context_inst = pa_context_new(pa_threaded_mainloop_get_api(pa_threaded_mainloop_inst), "AutoStep");
  cout << "context: " << pa_context_inst << endl;

  pa_context_set_state_callback(pa_context_inst, context_state_cb, this);

  error = pa_context_connect(pa_context_inst, NULL, (pa_context_flags_t) 0, NULL);
  if (error) fail_with_pa_error(error, __FILE__, __LINE__);



}

void AutoStep::Player::start(void) {
  should_play = true;

  // Just play - more complication may be added at a later date

  int error=0;

}

void AutoStep::Player::stop(void) {
  pa_stream_cork(playback_stream, 1, NULL, NULL);
}

double AutoStep::Player::duration() {
  return root_sound->duration();
}

