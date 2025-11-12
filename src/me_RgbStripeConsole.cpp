// RGB LED serial interface

/*
  Author: Martin Eden
  Last mod.: 2025-11-12
*/

#include <me_RgbStripeConsole.h>

#include <me_RgbStripe.h>
#include <me_Console.h>

using
  me_RgbStripe::TRgbStripe,
  me_RgbStripe::TColor;

static TBool ParseColor(
  TColor * Color
)
{
  if (!Console.Read(&Color->Red))
    return false;
  if (!Console.Read(&Color->Green))
    return false;
  if (!Console.Read(&Color->Blue))
    return false;

  return true;
}

static void PrintColor(
  TColor Color
)
{
  Console.Print(Color.Red);
  Console.Print(Color.Green);
  Console.Print(Color.Blue);
  Console.EndLine();
}

// ( RGB stripe handlers

/*
  Send data to stripe
*/
void me_RgbStripeConsole::Display(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  Stripe->Display();
}

/*
  Set pixels to initial state (zeroes)
*/
void me_RgbStripeConsole::Clear(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  Stripe->Clear();
}

/*
  Get stripe length

  Output

    TUint_2 -- Length
*/
void me_RgbStripeConsole::GetLength(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Length = Stripe->GetLength();

  Console.Print(Length);
  Console.EndLine();
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
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Index;
  TColor Color;

  if (!Console.Read(&Index)) return;

  if (!Stripe->GetPixel(&Color, Index)) return;

  PrintColor(Color);
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
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Index;
  TColor Color;

  if (!Console.Read(&Index)) return;

  if (!ParseColor(&Color)) return;

  Stripe->SetPixel(Index, Color);
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
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;
  const TColor FailColor = { 0, 0, 0 };

  TUint_2 StartIndex, StopIndex;
  TUint_2 Index;
  TColor Color;

  if (!Console.Read(&StartIndex)) return;
  if (!Console.Read(&StopIndex)) return;

  for (Index = StartIndex; Index <= StopIndex; ++Index)
  {
    if (!Stripe->GetPixel(&Color, Index))
      Color = FailColor;

    PrintColor(Color);
  }
}

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
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 StartIndex, StopIndex;
  TUint_2 Index;
  TColor Color;

  if (!Console.Read(&StartIndex)) return;
  if (!Console.Read(&StopIndex)) return;

  for (Index = StartIndex; Index <= StopIndex; ++Index)
  {
    if (!ParseColor(&Color)) return;

    Stripe->SetPixel(Index, Color);
  }
}

// ) Pixels range

/*
  Just display some pattern with no questions asked
*/
void me_RgbStripeConsole::RunTest(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  Clear(Data, Instance);

  // Light-up border and middle pixels. Stolen from [me_RgbStripe.Example].
  {
    const TColor
      Blue = { 0x00, 0x00, 0xFF },
      Green = { 0x00, 0xFF, 0x00 };

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
  2024 # # # # #
  2025-09-01
  2025-11-12
*/
