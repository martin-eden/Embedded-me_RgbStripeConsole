// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2026-01-10
*/

/*
  This sketch uses [me_Menu] to provide text interface to class instance.

  My Lua interface actually relies on this as on firmware.
  So renaming commands will require similar changes at that side.
*/

/*
  Footprint history

              Code  Mem  Notes
              8868  353
  2025-08-22  7246  401  Removed printf_P(PSTR())
  2025-08-26  7892  434  No more <.Bytes> in memory segment
  2025-08-27  8014  434  Address segment in base types now
  2025-09-01  8598  452  Streams
  2025-09-04  8482  429  Removed [me_SerialTokenizer]
  2025-11-12  8734  411
  2025-11-12  7888  539  Interface reduction
*/

#include <me_RgbStripeConsole.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Menu.h>
#include <me_RgbStripe.h>

const TUint_1 StripePin = 2;
const TUint_2 StripeLength = 60;

const TUint_2 DataMemSize = StripeLength * sizeof(me_RgbStripe::TColor);

TUint_1 DataMem[DataMemSize];

/*
  [handy] Add command to menu
*/
void AddCommand(
  me_Menu::TMenu * Menu,
  const TAsciiz Command,
  const TAsciiz Description,
  TMethod Handler,
  me_RgbStripe::TRgbStripe * Stripe
)
{
  Menu->AddItem(
    me_Menu::Freetown::ToItem(
      Command,
      Description,
      Handler,
      (TUint_2) Stripe
    )
  );
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

  AddCommand(Menu, "D", "Display", Display, Stripe);
  AddCommand(Menu, "C", "Clear pixels", Clear, Stripe);
  AddCommand(Menu, "T", "Run test", RunTest, Stripe);

  AddCommand(Menu, "SP", "Set pixel. (idx r g b)()", SetPixel, Stripe);
  AddCommand(Menu, "GP", "Get pixel. (idx)(r g b)", GetPixel, Stripe);

  AddCommand(Menu, "SPR", "Set pixels range. (start_i end_i (r g b)..)()", SetPixels, Stripe);
  AddCommand(Menu, "GPR", "Get pixels range. (start_i end_i)((r g b)..))", GetPixels, Stripe);

  AddCommand(Menu, "GL", "Get length. ()(len)", GetLength, Stripe);
}

// Setup stripe, setup and run menu
void RunTest()
{
  const TAddressSegment DataSeg = M_AsAddrSeg(DataMem);

  me_RgbStripe::TRgbStripe Stripe;
  me_Menu::TMenu Menu;

  Stripe.Init(StripePin, DataSeg);

  AddCommands(&Menu, &Stripe);
  Menu.AddBuiltinCommands();

  Menu.Print();
  Menu.Run();
}

void setup()
{
  Console.Init();
  Console.Print("NeoPixel RGB stripe console");
  RunTest();
  Console.Print("Done");
}

void loop()
{
}

/*
  2024-09-09
  2024-09-11 Lol I started this two months ago under name "me_Console_LedStripe"
  2024-09-17
  2024-09-27
  2024-10-18
  2025-08-22
  2025-11-12
*/
