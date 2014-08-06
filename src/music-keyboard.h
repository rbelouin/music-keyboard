#ifndef MUSIC_KEYBOARD_H
#define MUSIC_KEYBOARD_H

#include <portmidi.h>
#include <porttime.h>

#define MK_BUFFER_SIZE 1024
#define MK_TIMER_RESOLUTION 10

typedef struct mk_InputDevice {
  PmDeviceID id;
  PmDeviceInfo *info;
  PortMidiStream* stream;
} mk_InputDevice;

typedef struct mk_InputDeviceList {
  int length;
  mk_InputDevice* devices;
} mk_InputDeviceList;

typedef struct mk_Note {
  char* name;
  char* octave;
  struct mk_Note* next;
} mk_Note;

typedef struct mk_NoteList {
  int length;
  mk_Note* first;
  mk_Note* last;
} mk_NoteList;

typedef struct mk_State {
  int recording;
  int running;

  int sustainCount;
  PmTimestamp sustainTimestamp;

  mk_InputDeviceList inputDevices;
  mk_NoteList notes;
} mk_State;

mk_State mk_initState();
void mk_startListening(mk_State* state);

mk_InputDeviceList mk_getInputDevices();
void mk_displayInputDevices(mk_InputDeviceList list);
void mk_displayInputDevice(PmDeviceID id);

void mk_pollEvents(PtTimestamp timestamp, void* data);
void mk_processEvents(mk_State* state, PmEvent buffer[], int length);
void mk_processEvent(mk_State* state, PmEvent event);

void mk_addNote(mk_State* state, PmMessage message);
void mk_displayNotes(mk_NoteList notes);

#endif
