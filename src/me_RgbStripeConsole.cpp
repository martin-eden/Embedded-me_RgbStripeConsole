// RGB LED serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-09
*/

#include "me_RgbStripeConsole.h"

void me_RgbStripeConsole::Display_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  Stripe->Display();
}

void me_RgbStripeConsole::Reset_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  Stripe->Reset();
}

void me_RgbStripeConsole::RunTest_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  Stripe->Reset();

  {
    me_Ws2812b::TPixel Blue, Green;

    Blue = { .Green = 0, .Red = 0, .Blue = 0xFF };
    Green = { .Green = 0xFF, .Red = 0, .Blue = 0 };

    TUint_2 StripeLength = Stripe->GetLength();

    Stripe->SetPixel(0, Blue);
    Stripe->SetPixel(StripeLength / 2, Blue);
    Stripe->SetPixel(StripeLength / 2 + 1, Green);
    Stripe->SetPixel(StripeLength - 1, Blue);
  }

  Stripe->Display();
}

void me_RgbStripeConsole::SetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  me_Ws2812b::TPixel Pixel;

  TUint_2 Index = 0;

  Pixel.Red = 255;
  Pixel.Green = 0;
  Pixel.Blue = 255;

  Stripe->SetPixel(Index, Pixel);
}

void me_RgbStripeConsole::GetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  TUint_2 Index;
  me_Ws2812b::TPixel Pixel;

  Index = 0;

  Stripe->GetPixel(Index, &Pixel);

  printf("%u (%u %u %u)\n", Index, Pixel.Red, Pixel.Green, Pixel.Blue);
}

/*
  2024-09-09
*/
