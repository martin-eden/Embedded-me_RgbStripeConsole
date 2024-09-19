# What

(2024-09)

Serial text interface for my [RGB stripe class][me_RgbStripe].


## Example interaction

There is text serial interface implemented via my [menu][me_Menu] library.

After greetings sketch prints list of available commands:
```
[me_RgbStripeConsole] Okay, we are here.
--
? - List commands
^ - Exit
D - Display
R - Reset
T - Run test
SP - Set pixel components. (index red green blue)()
GP - Get pixel components. (index)(red green blue)
GL - Get stripe length. ()(length)
SL - Set stripe length. (length)()
==
```

Then you can send command and arguments (for commands like set pixel).
You can send several commands. Delimiter is space or newline.
On your machine you can create simple scripts like
setting pixels (12, 30 and 48) to (blue, green and red):

```
R
SP 12 0 0 255
SP 30 0 255 0
SP 48 255 0 0
D
```

Copy-pasting from editor is a lot funnier that typing commands every
time.

You can even write file sender in your favorite language to send
those snippets.


## Code

* [Example](examples/me_RgbStripeConsole/me_RgbStripeConsole.ino)
* [Interface](src/me_RgbStripeConsole.h)
* [Implementation](src/me_RgbStripeConsole.cpp)


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

* [My other embedded C++ libraries](https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts)
* [My other repositories](https://github.com/martin-eden/contents)

[me_RgbStripe]: https://github.com/martin-eden/Embedded-me_RgbStripe
[me_Menu]: https://github.com/martin-eden/Embedded-me_Menu
