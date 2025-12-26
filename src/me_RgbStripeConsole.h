// Menu interface items for RGB LED stripe

/*
  Author: Martin Eden
  Last mod.: 2025-12-26
*/

#pragma once

#include <me_BaseTypes.h>

// Stripe menu handlers
namespace me_RgbStripeConsole
{
  // Send data to stripe. ()()
  void Display(TUint_2, TUint_2 Stripe);
  // Set all colors to black. ()()
  void Clear(TUint_2, TUint_2 Stripe);

  // Get stripe length. ()(Length)
  void GetLength(TUint_2, TUint_2 Stripe);

  // Get pixel. (Index)(Red Green Blue)
  void GetPixel(TUint_2, TUint_2 Stripe);
  // Set pixel. (Index Red Green Blue)()
  void SetPixel(TUint_2, TUint_2 Stripe);

  // [Handy] Get pixels. (StartIdx EndIdx)((Red Green Blue)..)
  void GetPixels(TUint_2, TUint_2 Stripe);
  // [Handy] Set pixels. (StartIdx EndIdx (Red Green Blue)..)()
  void SetPixels(TUint_2, TUint_2 Stripe);

  // [Handy] Just display some pattern with no questions asked. ()()
  void RunTest(TUint_2, TUint_2 Stripe);
}

/*
  2024-09-09
  2024-09-17
  2024-09-27 Range of pixels
*/
