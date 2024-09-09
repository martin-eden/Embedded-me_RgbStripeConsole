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

#include <me_RgbStripeConsole.h>

using
  me_BaseTypes::TUint_1,
  me_BaseTypes::TUint_2;

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
// ) Stripe manager menu handlers

TRgbStripeManager RgbStripeManager;

// Add commands
void AddCommands(me_Menu::TMenu * Menu)
{
  me_Menu::TMenuItem Item;

  Item.Command.Set("R");
  Item.Description.Set("Reset");
  Item.Handler.Set(Reset_handler, (TUint_2) &RgbStripeManager);
  Menu->Add(&Item);

  Item.Command.Set("T");
  Item.Description.Set("Run test");
  Item.Handler.Set(RunTest_handler, (TUint_2) &RgbStripeManager);
  Menu->Add(&Item);
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
*/
