// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-10-13
*/

/*
  This sketch uses [me_Menu] to provide text interface to class instance.

  My Lua interface actually relies on this as on firmware.
  So renaming commands will require similar changes at that side.
*/

#include <me_RgbStripeConsole.h>

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>

#include <me_RgbStripe.h>
#include <me_Menu.h>

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Fast_Bps);
  Serial.setTimeout(15);

  InstallStandardStreams();

  RunTest();
}

void loop()
{
}

//--

/*
  [handy] Add command to menu
*/
void AddCommand(
  me_Menu::TMenu * Menu,
  const TChar * Command,
  const TChar * Description,
  me_RgbStripe::TRgbStripe * Stripe,
  TMethod Handler
)
{
  me_Menu::TMenuItem Item;

  Item.Command.LoadFrom(Command);
  Item.Description.LoadFrom(Description);
  Item.Handler.Set(Handler, (TUint_2) Stripe);

  Menu->Add(&Item);
}

/*
  Add stripe-specific commands to menu
*/
void AddCommands(
  me_Menu::TMenu * Menu,
  me_RgbStripe::TRgbStripe * Stripe
)
{
  me_Menu::TMenuItem Item;

  // For short referring handlers from that namespace
  using namespace me_RgbStripeConsole;

  AddCommand(Menu, "D", "Display", Stripe, Display);
  AddCommand(Menu, "R", "Reset pixels", Stripe, Reset);
  AddCommand(Menu, "T", "Run test", Stripe, RunTest);

  AddCommand(Menu, "SP", "Set pixel. (idx r g b)()", Stripe, SetPixel);
  AddCommand(Menu, "GP", "Get pixel. (idx)(r g b)", Stripe, GetPixel);

  AddCommand(Menu, "SPR", "Set pixels range. (start_i end_i (r g b)..)()", Stripe, SetPixels);
  AddCommand(Menu, "GPR", "Get pixels range. (start_i end_i)((r g b)..))", Stripe, GetPixels);

  AddCommand(Menu, "GL", "Get length. ()(len)", Stripe, GetLength);
  AddCommand(Menu, "SL", "Set length. (len)()", Stripe, SetLength);
  AddCommand(Menu, "GOP", "Get output pin. ()(pin)", Stripe, GetOutputPin);
  AddCommand(Menu, "SOP", "Set output pin. (pin)()", Stripe, SetOutputPin);
}

// Setup stripe, setup and run menu
void RunTest()
{
  // LED stripe instance
  me_RgbStripe::TRgbStripe Stripe;

  // Setup stripe
  {
    // You can change output pin and stripe length later from console
    TUint_1 StripePin = 2;
    TUint_2 NumLeds = 60;

    if (!Stripe.Init(StripePin, NumLeds))
    {
      printf_P(PSTR("Failed to init stripe. No memory for that length?\n"));
      return;
    }
  }

  // Setup menu, list commands and run
  {
    // Menu instance
    me_Menu::TMenu Menu;

    Menu.AddBuiltinCommands();

    AddCommands(&Menu, &Stripe);

    Menu.Print();

    Menu.Run();
  }
}

/*
  2024-09-09
  2024-09-11 Lol I started this two months ago under name "me_Console_LedStripe"
  2024-09-17
  2024-09-27
*/
