// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-09
*/

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>
#include <me_Menu.h>
#include <me_Ws2812b.h>
#include <me_StoredCall.h>

#include <me_RgbStripeConsole.h>

using
  me_BaseTypes::TBool,
  me_BaseTypes::TChar,
  me_BaseTypes::TUint_1,
  me_BaseTypes::TUint_2,
  me_BaseTypes::TMethod;

void setup()
{
  InstallStandardStreams();

  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);

  Serial.setTimeout(15);

  RunTest();
}

void loop()
{
}

//--

// ( RGB stripe serial manager

class TRgbStripeManager
{
  private:
    me_Ws2812b::TLedStripeState StripeState;
    TUint_1 OutputPin;
    TUint_2 StripeLength;
    me_Ws2812b::TPixel Pixels[60]; // fuck this, I'm sketching!

  public:
    void Init();
    void Reset();
    void Test();
    TBool SetPixel(TUint_2 Index, me_Ws2812b::TPixel Color);
    TBool GetPixel(TUint_2 Index, me_Ws2812b::TPixel * Color);
};

void TRgbStripeManager::Init()
{
  this->OutputPin = A0;
  this->StripeLength = 60;

  this->StripeState.Pixels = this->Pixels;
  this->StripeState.Length = this->StripeLength;
  this->StripeState.Pin = this->OutputPin;

  this->Reset();
}

void TRgbStripeManager::Reset()
{
  for (TUint_1 Index = 0; Index < this->StripeLength; ++Index)
    this->Pixels[Index] = { .Green = 0, .Red = 0, .Blue = 0 };

  me_Ws2812b::SetLedStripeState(this->StripeState);
}

void TRgbStripeManager::Test()
{
  Reset();

  TUint_2 Index;

  Index = 0;
  this->Pixels[Index] = { .Green = 0, .Red = 0, .Blue = 0xFF };

  Index = this->StripeLength / 2;
  this->Pixels[Index] = { .Green = 0, .Red = 0, .Blue = 0xFF };

  Index = (this->StripeLength / 2) + 1;
  this->Pixels[Index] = { .Green = 0xFF, .Red = 0, .Blue = 0 };

  Index = this->StripeLength - 1;
  this->Pixels[Index] = { .Green = 0, .Red = 0, .Blue = 0xFF };

  me_Ws2812b::SetLedStripeState(this->StripeState);
}

TBool TRgbStripeManager::SetPixel(
  TUint_2 Index __attribute__((unused)),
  me_Ws2812b::TPixel Color __attribute__((unused))
)
{
  this->Pixels[Index] = Color;

  me_Ws2812b::SetLedStripeState(this->StripeState);

  return true;
}

TBool TRgbStripeManager::GetPixel(
  TUint_2 Index __attribute__((unused)),
  me_Ws2812b::TPixel * Color __attribute__((unused))
)
{
  return false;
}

// ) RGB stripe serial manager

// ( Stripe manager menu handlers
void Reset_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripeManager * StripeManager = (TRgbStripeManager *) Instance;
  StripeManager->Reset();
}

void RunTest_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripeManager * StripeManager = (TRgbStripeManager *) Instance;
  StripeManager->Test();
}

void GetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripeManager * StripeManager = (TRgbStripeManager *) Instance;

  TUint_2 Index;
  me_Ws2812b::TPixel Pixel;

  Index = 0;

  StripeManager->GetPixel(Index, &Pixel);
}

void SetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripeManager * StripeManager = (TRgbStripeManager *) Instance;

  me_Ws2812b::TPixel Pixel;

  TUint_2 Index = 10;

  Pixel.Red = 255;
  Pixel.Green = 0;
  Pixel.Blue = 255;

  StripeManager->SetPixel(Index, Pixel);
}
// ) Stripe manager menu handlers

TRgbStripeManager RgbStripeManager;

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
  Item.Handler.Set(Handler, (TUint_2) &RgbStripeManager);

  Menu->Add(&Item);
}

// Add commands
void AddCommands(me_Menu::TMenu * Menu)
{
  me_Menu::TMenuItem Item;

  AddCommand(Menu, "R", "Reset", Reset_handler);
  AddCommand(Menu, "T", "Run test", RunTest_handler);
  AddCommand(Menu, "GetPixel", "Get pixel components", GetPixel_handler);
  AddCommand(Menu, "SetPixel", "Set pixel components", SetPixel_handler);
}

// Menu life
void RunTest()
{
  printf("[me_RgbStripeConsole] Okay, we are here.\n");

  RgbStripeManager.Init();

  me_Menu::TMenu Menu;
  AddCommands(&Menu);
  Menu.AddBuiltinCommands();
  Menu.Print();
  Menu.Run();

  printf("[me_RgbStripeConsole] Done.\n");
}

/*
  2024-09-09
  2024-09-11 Lol I started this two months ago under name "me_Console_LedStripe"
*/
