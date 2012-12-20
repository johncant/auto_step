#ifndef __NOTE_H__
#define __NOTE_H__

// An note is an object which produces a sound value at a given time
namespace AutoStep {
  class Note {
    double output(double time);
  };
}

#endif
