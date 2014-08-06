#include "music-keyboard.h"

int main(int argc, const char **argv) {
  mk_State state = mk_initState();

  mk_startListening(&state);
  mk_displayNotes(state.notes);

  return 0;
}
