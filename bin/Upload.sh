#!/bin/bash

# Just upload compiled binary

# Author: Martin Eden
# Last mod.: 2025-11-12

# "Works on my machine.."

avrdude \
  -U flash:w:me_RgbStripeConsole.ino.hex:i \
  -P /dev/ttyUSB0 \
  -b 115200 \
  -C ATmega328.avrdude.conf \
  -p atmega328p \
  -c arduino \
  -D \
  -qq

echo "Code loaded to board."

# 2024-10-13
# 2025-09-19
