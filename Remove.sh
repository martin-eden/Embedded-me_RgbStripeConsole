#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_RgbStripeConsole

# Uninstall dependencies
arduino-cli lib uninstall \
  me_ParseInteger \
  me_SerialTokenizer \
  me_RgbStripe \
  me_Menu \
  me_Uart \
  me_UartSpeeds \
  me_InstallStandardStreams \
  me_ManagedMemory \
  me_MemorySegment \
  me_BaseTypes
