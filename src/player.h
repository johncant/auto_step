#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <deque>
#include "sound.h"
#include <boost/smart_ptr/intrusive_ptr.hpp>

// pulse
#include <pulse/pulseaudio.h>


// This class plays a sound from start to finish. The sound would typically be an instance of AutoStep::Instruments::Mixer::Sound

namespace AutoStep {
  class Player {
    protected:
    bool should_play;
    double player_current_time;
    pa_threaded_mainloop *pa_threaded_mainloop_inst;
    pa_stream *playback_stream;
    pa_context *pa_context_inst;


    public:
    void write_to_pulseaudio(size_t nbytes); // Don't call this from outside the implementation
    void context_ready();

    boost::intrusive_ptr<AutoStep::Sound> root_sound;

    Player(const boost::intrusive_ptr<AutoStep::Sound> _root_sound);
    ~Player();
    void start();  // Tell the player to start/continue
    void stop(); // Tell the player to stop
    double current_time();
    double duration();
  };

}

#endif
