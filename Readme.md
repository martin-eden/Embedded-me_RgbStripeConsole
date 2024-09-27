# What

(2024-09)

Serial text interface for my [RGB stripe class][me_RgbStripe].


## Example interaction

There is text serial interface implemented via my [menu][me_Menu] library.

After greetings sketch prints list of available commands:
```
--
? - List commands
^ - Exit
D - Display
R - Reset pixels
T - Run test
SP - Set pixel. (index red green blue)()
GP - Get pixel. (index)(red green blue)
SPR - Set pixels range. (start_i end_i (r g b)..)()
GPR - Get pixels range. (start_i end_i)((r g b)..))
GL - Get stripe length. ()(length)
SL - Set stripe length. (length)()
GOP - Get stripe output pin. ()(pin)
SOP - Set stripe output pin. (pin)()
==
```

Then you can send command and arguments (for commands like set pixel).
You can send several commands. Delimiter is space or newline.
On your machine you can create simple scripts like
setting pixels (12, 30 and 48) to (red, green and blue):

```
SP 12 255 0 0
SP 30 0 255 0
SP 48 0 0 255
D
```

Copy-pasting from editor is a lot funnier that typing commands every
time.

You can even write file sender in your favorite language to send
those snippets. (I wrote [mine in Lua][Lua-RgbStripeConsole]).


## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]


## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```


## See also

* [Lua client][Lua-RgbStripeConsole]
* [My other embedded C++ libraries](https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts)
* [My other repositories](https://github.com/martin-eden/contents)

[Example]: examples/me_RgbStripeConsole/me_RgbStripeConsole.ino
[Interface]: src/me_RgbStripeConsole.h
[Implementation]: src/me_RgbStripeConsole.cpp
[Lua-RgbStripeConsole]: https://github.com/martin-eden/Lua-RgbStripeConsole
[me_RgbStripe]: https://github.com/martin-eden/Embedded-me_RgbStripe
[me_Menu]: https://github.com/martin-eden/Embedded-me_Menu
