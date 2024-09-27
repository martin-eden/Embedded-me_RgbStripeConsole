// RGB LED serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-27
*/

#include "me_RgbStripeConsole.h"

#include <me_RgbStripe.h>

#include <stdio.h> // printf()
#include <me_SerialTokenizer.h> // used in ReadWordInt()
#include <me_ParseInteger.h> // used in ReadWordInt()
#include <me_ManagedMemory.h> // used in ReadWordInt()

using
  me_RgbStripe::TRgbStripe,
  me_RgbStripe::TColor;

// ( I should move these to more generic module

// Read decimal integer in range [0, 65535] from stdin
TBool ReadWordInt(TUint_2 * Word)
{
  *Word = 0;

  me_ManagedMemory::TManagedMemory Buffer;

  const TUint_1 BufferSize = 6;

  /*
    TManagedMemory will call .Release() upon object death.
    So we may not call it explicitly.
  */
  Buffer.Reserve(BufferSize);

  me_SerialTokenizer::TCapturedEntity Entity;

  if (!me_SerialTokenizer::GetEntity(&Entity, Buffer))
    return false;

  if (Entity.IsTrimmed)
    return false;

  if (!me_ParseInteger::AsciiToUint2(Word, Entity.Segment))
    return false;

  return true;
}

// Read decimal integer in range [0, 255] from stdin
TBool ReadByteInt(TUint_1 * Byte)
{
  TUint_2 Word;

  if (!ReadWordInt(&Word))
    return false;

  if (Word > 255)
    return false;

  *Byte = Word;

  return true;
}

// ) Move these to more generic module

// ( RGB stripe handlers

/*
  Send data to stripe
*/
void me_RgbStripeConsole::Display_handler(
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
void me_RgbStripeConsole::Reset_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  Stripe->Reset();
}

/*
  Set pixel in memory

  We will read from stdin (or serial). We return nothing.

  What if we did not read enough data or data is not suitable?

  Before reading data we set index and pixel to some default values.
  Reading valid data overwrites these values. Reading bad data just
  jumps to pixel writing code.

  Input:

    TUint_2 -- Index
    TUint_1 -- Red
    TUint_1 -- Green
    TUint_1 -- Blue
*/
void me_RgbStripeConsole::SetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Index = 0;
  TColor Color = { .Red = 0, .Green = 0, .Blue = 0 };

  {
    if (!ReadWordInt(&Index)) goto Anyway;
    if (!ReadByteInt(&Color.Red)) goto Anyway;
    if (!ReadByteInt(&Color.Green)) goto Anyway;
    if (!ReadByteInt(&Color.Blue)) goto Anyway;
  }

  Anyway:

  if (!Stripe->SetPixel(Index, Color))
  {
    // Well, we don't print anything on bad data on this contract.
    return;
  }
}

/*
  Get pixel value

  We will read index from stdin and write color to stdout.

  If index is bad, we will return without writing to stdout.

  Input:

    TUint_2 -- Index

  Output:

    TUint_1 -- Red
    TUint_1 -- Green
    TUint_1 -- Blue
*/
void me_RgbStripeConsole::GetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Index;

  if (!ReadWordInt(&Index))
    return;

  TColor Color;

  if (!Stripe->GetPixel(Index, &Color))
    return;

  printf("%u %u %u\n", Color.Red, Color.Green, Color.Blue);
}

/*
  Get output pin

  Output

    TUint_1 -- Output pin
*/
void me_RgbStripeConsole::GetOutputPin_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_1 OutputPin = Stripe->GetOutputPin();

  printf("%u\n", OutputPin);
}

/*
  Set output pin

  Input

    TUint_1 -- Output pin
*/
void me_RgbStripeConsole::SetOutputPin_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_1 OutputPin;

  if (!ReadByteInt(&OutputPin))
    return;

  if (!Stripe->SetOutputPin(OutputPin))
    return;
}

/*
  Get stripe length

  Output

    TUint_2 -- Length
*/
void me_RgbStripeConsole::GetLength_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Length = Stripe->GetLength();

  printf("%u\n", Length);
}

/*
  Set stripe length

  Input

    TUint_2 -- Length
*/
void me_RgbStripeConsole::SetLength_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TRgbStripe * Stripe = (TRgbStripe *) Instance;

  TUint_2 Length;

  if (!ReadWordInt(&Length))
    return;

  if (!Stripe->SetLength(Length))
    return;
}

/*
  Just display some pattern with no questions asked
*/
void me_RgbStripeConsole::RunTest_handler(
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
*/
