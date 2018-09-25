#ifndef __XO_CONTROLLER_H_
#define __XO_CONTROLLER_H_

#include <nusys.h>

typedef enum {
  XO_BUTTON_A             = A_BUTTON,
  XO_BUTTON_B             = B_BUTTON,

  XO_BUTTON_START         = START_BUTTON,

  XO_BUTTON_TRIGGER_LEFT  = L_TRIG,
  XO_BUTTON_TRIGGER_RIGHT = R_TRIG,
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

// call on application startup
void xo_controller_Init(void);

// call once per frame
void xo_controller_Update(void);

// call to check if the controller is connected
u16 xo_contoller_IsConnected(u8 index);

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