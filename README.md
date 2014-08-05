music-keyboard
==============

Write music-suite scores with your MIDI keyboard.

How to install
--------------

For now, music-keyboard uses Apple CoreMIDI library and won't work on any other platform.

```sh
  make
  sudo make install # It will install music-keyboard in /usr/bin
```

If you are using Homebrew, you may want to install music-keyboard in a directory that you own:

```sh
  make install INSTALL_DIR=/usr/local/bin
```

TODO
----

- Use a portable MIDI library
- Emit sound while playing on the keyboard
- Emit keyboard events instead of writing to stdout

CHANGELOG
---------

- 05/08/2014: Manage all connected MIDI devices instead of just one.
