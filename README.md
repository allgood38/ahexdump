ahexdump
========

An arduino utility to dump input to the serial line in hex with nice
formatting.

Assumes you're using an Arduino UNO and the ino build system
<http://inotool.org/>. Uses the software serial library to listen to a device
and print the contents to the main serial line, each byte represented with two
hex digits. Line numbers applied to the left and a separator generated for
every specified number of tokens.

Strings are stored in program memory to conserve sram.
