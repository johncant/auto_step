#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "note.h"

AutoStep::Note::Note() {
  ref_count=0;
}


void intrusive_ptr_add_ref(AutoStep::Note *ptr) {
  ptr->ref_count++;
}

void intrusive_ptr_release(AutoStep::Note *ptr) {
  ptr->ref_count--;
  if (ptr->ref_count == 0) delete ptr;
}

