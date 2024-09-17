// Serial interface for RGB LED stripe

/*
  Author: Martin Eden
  Last mod.: 2024-09-17
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_RgbStripe.h>

#include <stdio.h> // printf()

namespace me_RgbStripeConsole
{
  // ( Stripe manager menu handlers
  void Display_handler(TUint_2 Data, TUint_2 Instance);

  void Reset_handler(TUint_2 Data, TUint_2 Instance);

  void RunTest_handler(TUint_2 Data, TUint_2 Instance);

  void SetPixel_handler(TUint_2 Data, TUint_2 Instance);
  void GetPixel_handler(TUint_2 Data, TUint_2 Instance);
  // ) Stripe manager menu handlers
}

/*
  2024-09-09
  2024-09-17
*/
