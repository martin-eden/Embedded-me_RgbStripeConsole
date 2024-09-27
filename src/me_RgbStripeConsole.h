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
    I cannot wrap these handlers in class because menu item handler
    needs that "void(TUint_2, TUint_2)" function address.

    I can meddle with implementation and pass in second argument
    not the pointer to stripe class but our class. But the state that
    this class will have is just pointer to stripe class.
    So it will be just identity wrapper.

    First argument is reserved for "data" and is always empty.
    Menu item have no additional data to pass in call.
  */

  // Send data to stripe
  void Display_handler(TUint_2 _, TUint_2 Stripe);

  // Zero data
  void Reset_handler(TUint_2 _, TUint_2 Stripe);

  // Set pixel. (Index Red Green Blue)()
  void SetPixel_handler(TUint_2 _, TUint_2 Stripe);
  // Get pixel. (Index)(Red Green Blue)
  void GetPixel_handler(TUint_2 _, TUint_2 Stripe);

  // Get stripe length. ()(Length)
  void GetLength_handler(TUint_2 _, TUint_2 Stripe);
  // Set stripe length. (Length)()
  void SetLength_handler(TUint_2 _, TUint_2 Stripe);

  // Get output pin. ()(OutputPin)
  void GetOutputPin_handler(TUint_2 _, TUint_2 Stripe);
  // Set output pin. (OutputPin)()
  void SetOutputPin_handler(TUint_2 _, TUint_2 Stripe);

  // [handy] Just display some pattern with no questions asked
  void RunTest_handler(TUint_2 _, TUint_2 Stripe);

  // ) Stripe manager menu handlers
}

/*
  2024-09-09
  2024-09-17
*/
