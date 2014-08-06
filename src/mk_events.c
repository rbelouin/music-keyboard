#include <stdio.h>
#include <stdlib.h>

#include "music-keyboard.h"

void mk_pollEvents(PtTimestamp timestamp, void* data) {
  mk_State* state = (mk_State*) data;

  PmEvent buffer[MK_BUFFER_SIZE];
  PmError error;

  for (int i = 0; i < state->inputDevices.length; i++) {
    error = Pm_Read(state->inputDevices.devices[i].stream, buffer, MK_BUFFER_SIZE);

    if (error < 0) {
      printf("%s: %s\n", state->inputDevices.devices[i].info->name, Pm_GetErrorText(error));
    }
    /* Otherwise, it isn't an error, but the count of events (sic) */
    else {
      mk_processEvents(state, buffer, error);
    }
  }
}

void mk_processEvents(mk_State* state, PmEvent buffer[], int length) {
  for (int i = 0; i < length; i++) {
    mk_processEvent(state, buffer[i]);
  }
}

void mk_processEvent(mk_State* state, PmEvent event) {
  PmMessage message = event.message;

  long status = Pm_MessageStatus(message);
  long data1 = Pm_MessageData1(message);
  long data2 = Pm_MessageData2(message);

  switch (status) {
    case 144:
      state->sustainCount = 0;
      state->sustainTimestamp = 0;

      if (state->recording) {
        mk_addNote(state, message);
      }
      break;
    case 176:
      if (data2 == 127) {
        if (state->sustainCount == 0) {
          state->sustainCount = 1;
          state->sustainTimestamp = event.timestamp;
        }
        else if (state->sustainCount == 1 && event.timestamp - state->sustainTimestamp < 500) {
          if (state->recording) {
            state->recording = 0;
            state->running = 0;
          }
          else {
            state->recording = 1;
            printf("recording…\n");
          }

          state->sustainCount = 0;
          state->sustainTimestamp = 0;
        }
        else {
          state->sustainCount = 1;
          state->sustainTimestamp = event.timestamp;
        }
      }
      break;
  }
}
