#ifndef __NOTE_H__
#define __NOTE_H__

// An note is an object which produces a sound value at a given time
namespace AutoStep {
  class Note;
}

void intrusive_ptr_add_ref(AutoStep::Note *ptr);
void intrusive_ptr_release(AutoStep::Note *ptr);


namespace AutoStep {
  class Note {
    private:
    friend void ::intrusive_ptr_add_ref(Note *ptr);
    friend void ::intrusive_ptr_release(Note *ptr);
    int ref_count;

    public:

    public:
    Note();
    virtual double output(double time)=0;
  };
}



#endif
