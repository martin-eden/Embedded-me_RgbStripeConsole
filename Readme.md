(2024-09)

## Example interaction

There is text serial interface implemented via my [me_Menu] library.

After greetings sketch prints list of available commands:
```
[me_RgbStripeConsole] Okay, we are here.
--
? - List commands
^ - Exit
D - Display
R - Reset
T - Run test
SP - Set pixel components
GP - Get pixel components
GL - Get stripe length
SL - Set stripe length
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
