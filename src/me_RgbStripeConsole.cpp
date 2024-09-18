// RGB LED serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-18
*/

#include "me_RgbStripeConsole.h"

#include <me_SerialTokenizer.h> // used in ReadWordInt()
#include <me_ParseInteger.h> // used in ReadWordInt()
#include <me_ManagedMemory.h> // used in ReadWordInt()

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
  Send data to stripe wrapper
*/
void me_RgbStripeConsole::Display_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  Stripe->Display();
}

/*
  Zero data wrapper
*/
void me_RgbStripeConsole::Reset_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

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

    Index: ui2
    Red: ui1
    Green: ui1
    Blue: ui1
*/
void me_RgbStripeConsole::SetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  TUint_2 Index = 0;
  me_Ws2812b::TPixel Pixel = { .Green = 0, .Red = 0, .Blue = 0 };

  {
    if (!ReadWordInt(&Index)) goto Anyway;
    if (!ReadByteInt(&Pixel.Red)) goto Anyway;
    if (!ReadByteInt(&Pixel.Green)) goto Anyway;
    if (!ReadByteInt(&Pixel.Blue)) goto Anyway;
  }

  Anyway:

  if (!Stripe->SetPixel(Index, Pixel))
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

    Index: ui2

  Output:

    Red: ui1
    Green: ui1
    Blue: ui1
*/
void me_RgbStripeConsole::GetPixel_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  TUint_2 Index;

  if (!ReadWordInt(&Index))
    return;

  me_Ws2812b::TPixel Pixel;

  if (!Stripe->GetPixel(Index, &Pixel))
    return;

  printf("%u %u %u\n", Pixel.Red, Pixel.Green, Pixel.Blue);
}

// Set stripe length. Input: Length
void me_RgbStripeConsole::SetLength_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  TUint_2 Length;

  if (!ReadWordInt(&Length))
    return;

  if (!Stripe->SetLength(Length))
    return;
}

// Get stripe length. Output: Length
void me_RgbStripeConsole::GetLength_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  TUint_2 Length = Stripe->GetLength();

  printf("%u\n", Length);
}

/*
  Just display some pattern with no questions asked
*/
void me_RgbStripeConsole::RunTest_handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  me_RgbStripe::TRgbStripe * Stripe = (me_RgbStripe::TRgbStripe *) Instance;

  Stripe->Reset();

  // Light-up border and middle pixels. Stolen from [me_RgbStripe.Example].
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

// ) RGB stripe handlers

/*
  2024-09-09
  2024-09-17
*/
