#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_RgbStripeConsole

# Uninstall dependencies
arduino-cli lib uninstall \
  me_RgbStripe \
  me_SerialTokenizer \
  me_ParseInteger \
  me_Menu \
  me_UartSpeeds \
  me_InstallStandardStreams \
  me_ManagedMemory \
  me_MemorySegment \
  me_MemoryPoint \
  me_BaseTypes
