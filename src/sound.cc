#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <iostream>
#include "sound.h"

AutoStep::Sound::Sound() {
  ref_count=0;
}


void intrusive_ptr_add_ref(AutoStep::Sound *ptr) {
  ptr->ref_count++;
}

void intrusive_ptr_release(AutoStep::Sound *ptr) {
  ptr->ref_count--;
  if (ptr->ref_count == 0) {
    std::cout << "DELETING" << std::endl;
    delete ptr;
  }
}

