// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-22
*/

/*
  This sketch uses [me_Menu] to provide text interface to class instance.

  My Lua interface actually relies on this as on firmware.
  So renaming commands will require similar changes at that side.
*/

/*
  Footprint history

  2025-08-22  Code  Mem  Notes
              8868  353
              7246  401  Removed printf_P(PSTR())
  2025-08-26  7816  434
              7892  434  No more <.Bytes> in memory segment
*/

#include <me_RgbStripeConsole.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Menu.h>
#include <me_RgbStripe.h>

void setup()
{
  Console.Init();

  Console.PrintProgmem(AsProgmemSeg("[me_RgbStripeConsole] Started."));
  RunTest();
  Console.PrintProgmem(AsProgmemSeg("[me_RgbStripeConsole] Done."));
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
  const TAsciiz Command,
  const TAsciiz Description,
  me_RgbStripe::TRgbStripe * Stripe,
  TMethod Handler
)
{
  using
    me_Menu::Freetown::ToItem;

  me_Menu::TMenuItem Item;

  Item = ToItem(Command, Description, Handler, (TUint_2) Stripe);

  Menu->AddItem(Item);
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

  // Menu instance
  me_Menu::TMenu Menu;

  // Setup menu
  {
    Menu.AddBuiltinCommands();

    AddCommands(&Menu, &Stripe);
  }

  // Setup stripe
  /*
    Initializing here to have space to resize pixels memory when
    changing stripe length.
  */
  {
    // We can change output pin and stripe length later from console
    TUint_1 StripePin = 2;
    TUint_2 NumLeds = 60;

    if (!Stripe.Init(StripePin, NumLeds))
    {
      Console.PrintProgmem(
        AsProgmemSeg("Failed to initialize stripe. No memory for that length?")
      );
      return;
    }
  }

  // Print menu commands and start handling them
  {
    Menu.Print();
    Menu.Run();
  }
}

/*
  2024-09-09
  2024-09-11 Lol I started this two months ago under name "me_Console_LedStripe"
  2024-09-17
  2024-09-27
  2024-10-18
  2025-08-22
*/
