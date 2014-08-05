#include <CoreServices/CoreServices.h>
#include <CoreMIDI/CoreMIDI.h>

#include "midi.h"

MIDICommand packet2command(MIDIPacket packet) {
  MIDICommand command = {0, 0, 0};

  if (packet.length) {
    command.code = packet.data[0];
    command.note = packet.data[1];
    command.velocity = packet.data[2];
  }

  return command;
}

void printNotes(State* state) {
  Note* iterator = state->notes.note;

  if (iterator != NULL) {
    printf("[");

    for (int i = 0; i < state->notes.count - 1; i++) {
      printf("%s%s, ", iterator->name, iterator->octave);
      iterator = iterator->next;
    }

    printf("%s%s]\n", iterator->name, iterator->octave);
  }

  state->running = 0;
}

void handleCommand(MIDICommand command, State* state) {
  static const char *noteNames[12] = {"c", "db", "d", "eb", "e", "f", "gb", "g", "ab", "a", "bb", "b"};
  static const char *octaveNames[11] = {"_____", "____", "___", "__", "_", "", "'", "''", "'''", "''''", "'''''"};

  int note;
  int octave;

  /* If the command is related to the sustain pedal */
  if (state->running && command.code == 176) {
    state->sustain = command.velocity == 0 ? 0 : 1;

    /* Start recording if the user presses it */
    if (state->sustain) {
      fprintf(stderr, "Start recording…\n");
    }
    else {
      printNotes(state);
    }
  }
  /* Else if we are recording, save the pressed note */
  else if (state->running && state->sustain && command.code == 144) {
    state->notes.count++;

    note = command.note % 12;
    octave = command.note / 12 % 11;

    state->lastNote = malloc(sizeof(Note));
    state->lastNote->name = (char*) noteNames[note];
    state->lastNote->octave = (char*) octaveNames[octave];
    state->lastNote->next = NULL;

    if (state->currentNote != NULL) {
      state->currentNote->next = state->lastNote;
    }
    else {
      state->notes.note = state->lastNote;
    }
    state->currentNote = state->lastNote;
  }
}

void readPackets(const MIDIPacketList* list, void* readProcRefCon, void* ref) {
  MIDIPacket* packet;

  if (list->numPackets > 0) {
    packet = (MIDIPacket*) &list->packet[0];

    for (int i = 0; i < list->numPackets; i++) {
      handleCommand(packet2command(*packet), (State *) ref);
    }
  }
}

void listenMIDIEndpoint(State* state, MIDIEndpointRef src) {
  MIDIClientRef client;
  MIDIPortRef port;

  CFStringRef name = NULL;

  /* Get the properties of the given endpoint */
  MIDIObjectGetStringProperty(src, kMIDIPropertyName, &name);

  /* Create a client and a port */
  MIDIClientCreate(name, NULL, NULL, &client);
  MIDIInputPortCreate(client, name, readPackets, NULL, &port);

  /* Link the port with the endpoint */
  MIDIPortConnectSource(port, src, state);

  /* Print instructions */
  fprintf(stderr, "listen to : %s\n", CFStringGetCStringPtr(name, kCFStringEncodingUTF8));
}

void listenMIDIEndpoints() {
  /* Initialize state */
  State state = {1, 0, {0, NULL}, NULL, NULL};

  for (int i = 0; i < MIDIGetNumberOfSources(); i++) {
    listenMIDIEndpoint(&state, MIDIGetSource(i));
  }

  /* Print instructions */
  fprintf(stderr, "Press sustain button while recording.\n\n");

  while (state.running) {
    sleep(1);
  }
}
