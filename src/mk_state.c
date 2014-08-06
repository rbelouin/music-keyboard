#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "music-keyboard.h"

mk_State mk_initState() {
  mk_State state = {0, 1, 0, 0, {0, NULL}, {0, NULL, NULL}};

  return state;
}

void mk_startListening(mk_State* state) {
  state->inputDevices = mk_getInputDevices();

  PmError error;

  Pt_Start(MK_TIMER_RESOLUTION, &mk_pollEvents, state);

  for (int i = 0; i < state->inputDevices.length; i++) {
    error = Pm_OpenInput(&state->inputDevices.devices[i].stream, state->inputDevices.devices[i].id, NULL, MK_BUFFER_SIZE, NULL, NULL);
    if (error != pmNoError) {
      fprintf(stderr, "%s: %s\n", state->inputDevices.devices[i].info->name, Pm_GetErrorText(error));
    }
  }

  printf("Double press the sustain button/pedal to enter in the recording mode, do it again to quit the recording mode.\n\n");

  while (state->running) {
    sleep(1);
  }
}
