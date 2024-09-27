// Serial interface for RGB LED stripe

/*
  Author: Martin Eden
  Last mod.: 2024-09-27
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_RgbStripeConsole
{
  // ( Stripe manager menu handlers

  /*
    Here are set of functions with fixed signature for use as handlers.

    They read arguments and write results to serial.

    First argument is reserved for "data" and is always empty.
    Menu item have no additional data to pass in call.

    Second argument is pointer to [TRgbStripe] class data.

    Most of them are just wrappings of class methods.

    Except for RunTest(), SetPixels() and GetPixels().
  */

  // Send data to stripe
  void Display(TUint_2 _, TUint_2 Stripe);

  // Zero data
  void Reset(TUint_2 _, TUint_2 Stripe);

  // Set pixel. (Index Red Green Blue)()
  void SetPixel(TUint_2 _, TUint_2 Stripe);
  // Get pixel. (Index)(Red Green Blue)
  void GetPixel(TUint_2 _, TUint_2 Stripe);

  // Set pixels. (StartIdx EndIdx (Red Green Blue)..)()
  void SetPixels(TUint_2 _, TUint_2 Stripe);
  // Get pixels. (StartIdx EndIdx)((Red Green Blue)..)
  void GetPixels(TUint_2 _, TUint_2 Stripe);

  // Get stripe length. ()(Length)
  void GetLength(TUint_2 _, TUint_2 Stripe);
  // Set stripe length. (Length)()
  void SetLength(TUint_2 _, TUint_2 Stripe);

  // Get output pin. ()(OutputPin)
  void GetOutputPin(TUint_2 _, TUint_2 Stripe);
  // Set output pin. (OutputPin)()
  void SetOutputPin(TUint_2 _, TUint_2 Stripe);

  // [handy] Just display some pattern with no questions asked
  void RunTest(TUint_2 _, TUint_2 Stripe);

  // ) Stripe manager menu handlers
}

/*
  2024-09-09
  2024-09-17
  2024-09-27 Range of pixels
*/
