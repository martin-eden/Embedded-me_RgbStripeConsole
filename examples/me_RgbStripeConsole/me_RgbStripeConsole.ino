// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-17
*/

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>
#include <me_Menu.h>
#include <me_StoredCall.h>
#include <me_Ws2812b.h>
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

// Add command
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

// Add commands
void AddCommands(me_Menu::TMenu * Menu)
{
  me_Menu::TMenuItem Item;

  AddCommand(Menu, "D", "Display", me_RgbStripeConsole::Display_handler);
  AddCommand(Menu, "R", "Reset", me_RgbStripeConsole::Reset_handler);
  AddCommand(Menu, "T", "Run test", me_RgbStripeConsole::RunTest_handler);
  AddCommand(Menu, "SP", "Set pixel components", me_RgbStripeConsole::SetPixel_handler);
  AddCommand(Menu, "GP", "Get pixel components", me_RgbStripeConsole::GetPixel_handler);
}

// Menu life
void RunTest()
{
  Stripe.Init(A0, 60);

  me_Menu::TMenu Menu;
  AddCommands(&Menu);
  Menu.AddBuiltinCommands();
  Menu.Print();
  Menu.Run();
}

/*
  2024-09-09
  2024-09-11 Lol I started this two months ago under name "me_Console_LedStripe"
  2024-09-17
*/
