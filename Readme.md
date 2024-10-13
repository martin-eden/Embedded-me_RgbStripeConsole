# What

(2024-09/2024-10)

Serial text interface for my [RGB stripe class][me_RgbStripe].


## Sample output

Serial speed 115200.

```
--
  ? - List commands
  ^ - Exit
  D - Display
  R - Reset pixels
  T - Run test
  SP - Set pixel. (idx r g b)()
  GP - Get pixel. (idx)(r g b)
  SPR - Set pixels range. (start_i end_i (r g b)..)()
  GPR - Get pixels range. (start_i end_i)((r g b)..))
  GL - Get length. ()(len)
  SL - Set length. (len)()
  GOP - Get output pin. ()(pin)
  SOP - Set output pin. (pin)()
==

```

There is text interface implemented via my [menu][me_Menu] library.

You can send command and arguments (for commands like set pixel).
You can send several commands. Delimiter is space or newline.
On your machine you can create simple scripts like
setting pixels (12, 30 and 48) to (red, green and blue):

```
R
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


## Installation

Setting up toolchain is a pain, I know.

Even more for my source code, because it's scattered among repos and
repos are evolving.

So I'm providing compiled binary. It may be not latest but stable
version I'm happy with.

* Use [Upload.sh](Upload.sh).

  It assumes you're under Linux and _apt-installed_ `avrdude`.

* Or use `arduino-cli`, collect libraries and compile:

  Run [Install.sh](Install.sh).


## Removal

Run [Remove.sh](Remove.sh).


## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```


## See also

* [RGB stripe class][me_RgbStripe]
* [Lua client][Lua-RgbStripeConsole]
* [My other embedded C++ libraries](https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts)
* [My other repositories](https://github.com/martin-eden/contents)

[Example]: examples/me_RgbStripeConsole/me_RgbStripeConsole.ino
[Interface]: src/me_RgbStripeConsole.h
[Implementation]: src/me_RgbStripeConsole.cpp
[Lua-RgbStripeConsole]: https://github.com/martin-eden/Lua-RgbStripeConsole
[me_RgbStripe]: https://github.com/martin-eden/Embedded-me_RgbStripe
[me_Menu]: https://github.com/martin-eden/Embedded-me_Menu
