music-keyboard
==============

Write music-suite scores with your MIDI keyboard.

How to install
--------------

You need [portmidi](http://portmedia.sourceforge.net/portmidi/) to build music-keyboard.

```sh
  make
  sudo make install # It will install music-keyboard in /usr/bin
```

You may want to install music-keyboard in a directory that you own:

```sh
  make install PREFIX=/usr/local # Install music-keyboard in /usr/local/bin
```

Although it is only tested on Mac OS X 10.9, music-keyboard should work on GNU/Linux and Windows too.

TODO
----

- Emit sound while playing on the keyboard
- Emit keyboard events instead of writing to stdout

CHANGELOG
---------

- 06/08/2014: Use PortMIDI (a MIDI library working on GNU/Linux, Mac OS X and Windows) instead of CoreMIDI (working only on Mac OS X).
- 05/08/2014: Manage all connected MIDI devices instead of just one.
