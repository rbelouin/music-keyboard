#ifndef test_midi_test_midi_h
#define test_midi_test_midi_h

#include <CoreMIDI/CoreMIDI.h>

typedef struct MIDICommand {
  unsigned int code;
  unsigned int note;
  unsigned int velocity;
} MIDICommand;

typedef struct Note {
  char *name;
  char *octave;
  struct Note *next;
} Note;

typedef struct NoteList {
  int count;
  struct Note *note;
} NoteList;

typedef struct State {
  int running;
  int sustain;

  NoteList notes;
  Note *currentNote;
  Note *lastNote;
} State;

MIDICommand packet2command(MIDIPacket packet);

void printNotes(State* state);
void handleNote(MIDICommand* command, State* state);
void listenMIDIEndpoints();

#endif
