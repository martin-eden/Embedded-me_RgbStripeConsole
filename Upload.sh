#!/bin/bash

# Just upload compiled binary

# Author: Martin Eden
# Last mod.: 2024-10-13

# "Works on my machine.."

avrdude \
  -C bin/avrdude.conf \
  -p atmega328p \
  -c arduino \
  -P /dev/ttyUSB0 \
  -b 115200 \
  -D \
  -U flash:w:bin/me_RgbStripeConsole.ino.hex:i \
  -qq

# 2024-10-13
