#ifndef __XO_CONTROLLER_H_
#define __XO_CONTROLLER_H_

#include <nusys.h>

typedef enum {
  XO_BUTTON_A             = A_BUTTON,
  XO_BUTTON_B             = B_BUTTON,

  XO_BUTTON_START         = START_BUTTON,

  XO_BUTTON_BUMPER_LEFT   = L_TRIG,
  XO_BUTTON_BUMPER_RIGHT  = R_TRIG,
  XO_BUTTON_TRIGGER_Z     = Z_TRIG,

  XO_BUTTON_D_UP          = U_JPAD,
  XO_BUTTON_D_DOWN        = D_JPAD,
  XO_BUTTON_D_LEFT        = L_JPAD,
  XO_BUTTON_D_RIGHT       = R_JPAD,

  XO_BUTTON_C_UP          = U_CBUTTONS,
  XO_BUTTON_C_DOWN        = D_CBUTTONS,
  XO_BUTTON_C_LEFT        = L_CBUTTONS,
  XO_BUTTON_C_RIGHT       = R_CBUTTONS
} Button_t;

typedef enum {
  XO_AXIS_STICK,
  XO_AXIS_DPAD,
  XO_AXIS_CPAD
} Axis_t;

//////////////////////////////////////////////////////////////////////////////////////////
// Setup
//////////////////////////////////////////////////////////////////////////////////////////

// call on application startup
void xo_controller_Init(void);

// call once per frame
void xo_controller_Update(void);

//////////////////////////////////////////////////////////////////////////////////////////
// State check
//////////////////////////////////////////////////////////////////////////////////////////

// call to check if the controller is connected
u16 xo_contoller_IsConnected(u8 index);

// number of standard controllers plugged in
u8 xo_controller_NumberConnected();

// get the index for the nth controller.
// examples:
//  If the first and third controller ports are plugged in this function maps:
//  0->0, 1->2, 2->0xff (invalid), 3->0xff (invalid)
//  If only the last controller port is plugged in:
//  0->3, 1->0xff (invalid), 2->0xff (invalid), 3->0xff (invalid)
u8 xo_controller_GetIndex(u8 nthController);

//////////////////////////////////////////////////////////////////////////////////////////
// Input polling methods
//////////////////////////////////////////////////////////////////////////////////////////

// Is down right now
u16 xo_controller_ButtonDown(u8 index, Button_t button);

// Is up right now
u16 xo_controller_ButtonUp(u8 index, Button_t button);

// Just went down this frame
u16 xo_controller_ButtonPressed(u8 index, Button_t button);

// Just came up this frame
u16 xo_controller_ButtonReleased(u8 index, Button_t button);

// -1 to 1 on each axis
void xo_controller_GetAxisUnclamped(u8 index, Axis_t axis, f32* xOut, f32* yOut);

// -1 to 1, max magnitude of 1
void xo_controller_GetAxisClamped(u8 index, Axis_t axis, f32* xOut, f32* yOut);

#endif // __XO_CONTROLLER_H_