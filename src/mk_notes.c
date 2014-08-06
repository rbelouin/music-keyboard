#include <stdio.h>
#include <stdlib.h>

#include "music-keyboard.h"

void mk_addNote(mk_State* state, PmMessage message) {
  static const char *noteNames[12] = {"c", "db", "d", "eb", "e", "f", "gb", "g", "ab", "a", "bb", "b"};
  static const char *octaveNames[11] = {"_____", "____", "___", "__", "_", "", "'", "''", "'''", "''''", "'''''"};

  long status = Pm_MessageStatus(message);
  long data1 = Pm_MessageData1(message);
  long data2 = Pm_MessageData2(message);

  mk_Note* note = malloc(sizeof(mk_Note));
  note->name = (char*) noteNames[data1 % 12];
  note->octave = (char*) octaveNames[data1 / 12 % 11];
  note->next = NULL;

  if (state->notes.first == NULL) {
    state->notes.first = note;
  }

  state->notes.length++;

  if (state->notes.last != NULL) {
    state->notes.last->next = note;
  }

  state->notes.last = note;
}

void mk_displayNotes(mk_NoteList notes) {
  mk_Note* cursor = notes.first;

  printf("[");
  if (cursor != NULL) {
    for (int i = 0; i < notes.length - 1; i++) {
      printf("%s%s,", cursor->name, cursor->octave);
      cursor = cursor->next;
    }
    printf("%s%s", cursor->name, cursor->octave);
  }
  printf("]\n");
}
