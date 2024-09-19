#!/bin/bash

# Install dependencies
arduino-cli \
  lib install \
    --git-url \
      https://github.com/martin-eden/Embedded-me_BaseTypes \
      https://github.com/martin-eden/Embedded-me_MemoryPoint \
      https://github.com/martin-eden/Embedded-me_MemorySegment \
      https://github.com/martin-eden/Embedded-me_ManagedMemory \
      https://github.com/martin-eden/Embedded-me_InstallStandardStreams \
      https://github.com/martin-eden/Embedded-me_UartSpeeds \
      https://github.com/martin-eden/Embedded-me_Menu \
      https://github.com/martin-eden/Embedded-me_RgbStripe \
      https://github.com/martin-eden/Embedded-me_SerialTokenizer \
      https://github.com/martin-eden/Embedded-me_ParseInteger

# Install library
arduino-cli \
  lib install \
    --git-url \
      https://github.com/martin-eden/Embedded-me_RgbStripeConsole
