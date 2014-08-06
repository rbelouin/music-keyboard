#include <stdio.h>
#include <stdlib.h>

#include "music-keyboard.h"

mk_InputDeviceList mk_getInputDevices() {
  int devicesCount = Pm_CountDevices();
  int cursor = 0;

  PmDeviceInfo* info;

  mk_InputDeviceList list = {0, NULL};

  for (int i = 0; i < devicesCount; i++) {
    info = (PmDeviceInfo*) Pm_GetDeviceInfo(i);

    if (info->input) {
      list.length++;
    }
  }

  list.devices = malloc(sizeof(mk_InputDevice) * list.length);

  for (int i = 0; i < devicesCount; i++) {
    info = (PmDeviceInfo*) Pm_GetDeviceInfo(i);

    if (info->input) {
      list.devices[cursor].id = i;
      list.devices[cursor].info = info;
      list.devices[cursor].stream = NULL;
      cursor++;
    }
  }

  return list;
}

void mk_displayInputDevices(mk_InputDeviceList list) {
  for (int i = 0; i < list.length; i++) {
    mk_displayInputDevice(list.devices[i].id);
  }
}

void mk_displayInputDevice(PmDeviceID id) {
  const PmDeviceInfo* info = Pm_GetDeviceInfo(id);

  if (info == NULL) {
    fprintf(stderr, "Default input device is not connected.\n");
  }
  else {
    printf("Use %s input device.\n", info->name);
  }
}
