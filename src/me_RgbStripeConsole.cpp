// RGB LED serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-10-30
*/

#include "me_RgbStripeConsole.h"

#include <me_RgbStripe.h>

#include <me_ReadInteger.h> // for reading integers, lol

#include <me_Console.h> // printing data to serial

using
  me_RgbStripe::TRgbStripe,
  me_RgbStripe::TColor,
  me_ReadInteger::Read_TUint_1,
  me_ReadInteger::Read_TUint_2;

// ( RGB stripe handlers

/*
  Send data to stripe
*/
void me_RgbStripeConsole::Display(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  Stripe->Display();
}

/*
  Zero data
*/
void me_RgbStripeConsole::Reset(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  Stripe->Reset();
}

/*
  Set pixel in memory

  We are reading from stdin (or serial). We return nothing.

  If we did not read enough data or data is not suitable,
  we just return.

  Input:

    TUint_2 -- Index
    TUint_1 -- Red
    TUint_1 -- Green
    TUint_1 -- Blue
*/
void me_RgbStripeConsole::SetPixel(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Index;
  TColor Color;

  if (!Read_TUint_2(&Index)) return;

  // Read color components
  {
    if (!Read_TUint_1(&Color.Red)) return;
    if (!Read_TUint_1(&Color.Green)) return;
    if (!Read_TUint_1(&Color.Blue)) return;
  }

  Stripe->SetPixel(Index, Color);
}

/*
  Get pixel value

  If index is bad, we return without writing.

  Input:

    TUint_2 -- Index

  Output:

    TUint_1 -- Red
    TUint_1 -- Green
    TUint_1 -- Blue
*/
void me_RgbStripeConsole::GetPixel(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Index;
  TColor Color;

  if (!Read_TUint_2(&Index)) return;

  if (!Stripe->GetPixel(Index, &Color)) return;

  Console.Print(Color.Red);
  Console.Print(Color.Green);
  Console.Print(Color.Blue);
  Console.EndLine();
}


// ( Pixels range

/*
  Our base class provides access to any pixel.

  However common communication scenario is setting all stripe
  pixels to different values. This can be transmitted as

    SP 1 11 11 11
    SP 0 10 10 10
    SP 2 12 12 12
    // Tokens = Pixels * 5

  Each pixel in transaction has unique index from range.
  So I would prefer just specify index range and transmit
  sequence of pixel colors:

    SPR 0 2 10 10 10 11 11 11 12 12 12
    // Tokens = Pixels * 3 + 3

  Not readable and less resilient but we are transmitting same data
  in less tokens. So what previously took 10 seconds now will take 6.
*/

/*
  Set pixels

  Additional functionality.

  Input:

    TUint_2 -- Start index
    TUint_2 -- Stop index
    (
      TUint_1 -- Red
      TUint_1 -- Green
      TUint_1 -- Blue
    ) ..
*/
void me_RgbStripeConsole::SetPixels(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 StartIndex, StopIndex;

  if (!Read_TUint_2(&StartIndex)) return;
  if (!Read_TUint_2(&StopIndex)) return;

  // Set pixels in range
  {
    TUint_2 Index;
    TColor Color;

    for (Index = StartIndex; Index <= StopIndex; ++Index)
    {
      if (!Read_TUint_1(&Color.Red)) return;
      if (!Read_TUint_1(&Color.Green)) return;
      if (!Read_TUint_1(&Color.Blue)) return;

      Stripe->SetPixel(Index, Color);
    }
  }
}

/*
  Get pixels

  Additional functionality.

  Input:

    TUint_2 -- Start index
    TUint_2 -- Stop index

  Output:

    (
      TUint_1 -- Red
      TUint_1 -- Green
      TUint_1 -- Blue
    ) ..
*/
void me_RgbStripeConsole::GetPixels(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 StartIndex, StopIndex;

  if (!Read_TUint_2(&StartIndex)) return;
  if (!Read_TUint_2(&StopIndex)) return;

  // Print pixels in range
  {
    TUint_2 Index;
    TColor Color;

    for (Index = StartIndex; Index <= StopIndex; ++Index)
    {
      if (!Stripe->GetPixel(Index, &Color)) break;

      Console.Print(Color.Red);
      Console.Print(Color.Green);
      Console.Print(Color.Blue);
      Console.Write("");
    }

    Console.EndLine();
  }
}

// ) Pixels range

/*
  Set output pin

  Input

    TUint_1 -- Output pin
*/
void me_RgbStripeConsole::SetOutputPin(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_1 OutputPin;

  if (!Read_TUint_1(&OutputPin)) return;

  if (!Stripe->SetOutputPin(OutputPin)) return;
}

/*
  Get output pin

  Output

    TUint_1 -- Output pin
*/
void me_RgbStripeConsole::GetOutputPin(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_1 OutputPin = Stripe->GetOutputPin();

  Console.Print(OutputPin);
  Console.EndLine();
}

/*
  Set stripe length

  Input

    TUint_2 -- Length
*/
void me_RgbStripeConsole::SetLength(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Length;

  if (!Read_TUint_2(&Length)) return;

  if (!Stripe->SetLength(Length)) return;
}

/*
  Get stripe length

  Output

    TUint_2 -- Length
*/
void me_RgbStripeConsole::GetLength(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Length = Stripe->GetLength();

  Console.Print(Length);
  Console.EndLine();
}

/*
  Just display some pattern with no questions asked
*/
void me_RgbStripeConsole::RunTest(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  Stripe->Reset();

  // Light-up border and middle pixels. Stolen from [me_RgbStripe.Example].
  {
    TColor Blue = { .Red = 0, .Green = 0, .Blue = 0xFF };
    TColor Green = { .Red = 0, .Green = 0xFF, .Blue = 0 };

    TUint_2 StripeLength = Stripe->GetLength();

    Stripe->SetPixel(0, Blue);
    Stripe->SetPixel(StripeLength / 2, Blue);
    Stripe->SetPixel(StripeLength / 2 + 1, Green);
    Stripe->SetPixel(StripeLength - 1, Blue);
  }

  Stripe->Display();
}

// ) RGB stripe handlers

/*
  2024-09-09
  2024-09-17
  2024-09-27
  2024-10-10
  2024-10-30
*/
