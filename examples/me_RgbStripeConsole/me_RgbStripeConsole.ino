// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-17
*/

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>
#include <me_Menu.h>
#include <me_RgbStripe.h>

#include <me_RgbStripeConsole.h>

void setup()
{
  InstallStandardStreams();

  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);

  Serial.setTimeout(15);

  printf("[me_RgbStripeConsole] Okay, we are here.\n");
  RunTest();
  printf("[me_RgbStripeConsole] Done.\n");
}

void loop()
{
}

//--

me_RgbStripe::TRgbStripe Stripe;

// [handy] Add command to menu
void AddCommand(
  me_Menu::TMenu * Menu,
  const TChar * Command,
  const TChar * Description,
  TMethod Handler
)
{
  me_Menu::TMenuItem Item;

  Item.Command.Set(Command);
  Item.Description.Set(Description);
  Item.Handler.Set(Handler, (TUint_2) &Stripe);

  Menu->Add(&Item);
}

// Add stripe-specific commands to menu
void AddCommands(me_Menu::TMenu * Menu)
{
  me_Menu::TMenuItem Item;

  using namespace me_RgbStripeConsole;

  AddCommand(Menu, "D", "Display", Display_handler);
  AddCommand(Menu, "R", "Reset", Reset_handler);
  AddCommand(Menu, "T", "Run test", RunTest_handler);
  AddCommand(Menu, "SP", "Set pixel components", SetPixel_handler);
  AddCommand(Menu, "GP", "Get pixel components", GetPixel_handler);
}

// Init stripe, then setup and run menu commands for that stripe
void RunTest()
{
  // Stripe setup
  {
    TUint_1 StripePin = A0;
    TUint_2 NumLeds = 60;

    Stripe.Init(StripePin, NumLeds);
  }

  // Menu setup, greeting screen and run
  {
    me_Menu::TMenu Menu;

    Menu.AddBuiltinCommands();

    AddCommands(&Menu);

    Menu.Print();

    Menu.Run();
  }
}

/*
  2024-09-09
  2024-09-11 Lol I started this two months ago under name "me_Console_LedStripe"
  2024-09-17
*/
