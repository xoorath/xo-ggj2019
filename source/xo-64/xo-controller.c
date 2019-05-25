#include <xo-controller.h>
#include <xo-math.h>
#include <STRING.H>

// TODO: Consider using the nusys controller code for current/last state checking.
static OSContPad s_ControllersCurrent[NU_CONT_MAXCONTROLLERS];
static OSContPad s_ControllersLast[NU_CONT_MAXCONTROLLERS];

void xo_controller_Init(void)
{
  nuContInit();
  nuContDataGetAll((OSContPad *)s_ControllersCurrent);
  memcpy((void *)s_ControllersLast, (void *)s_ControllersCurrent, sizeof(s_ControllersLast));
}

void xo_controller_Update(void)
{
  nuContQueryRead();
  memcpy((void *)s_ControllersLast, (void *)s_ControllersCurrent, sizeof(s_ControllersLast));
  nuContDataGetAll((OSContPad *)s_ControllersCurrent);
}

u16 xo_contoller_IsConnected(u8 index)
{
  if(index > NU_CONT_MAXCONTROLLERS)
  {
    return FALSE;
  }

  if(nuContStatus[index].errno)
  {
    return FALSE;
  }

  switch (nuContStatus[index].type & CONT_TYPE_MASK)
  {
  case CONT_TYPE_NORMAL:
    return TRUE;
  // A mouse, voice device, or something unknown
  default:
    return FALSE;
  }
}

u8 xo_controller_NumberConnected()
{
  u8 i;
  u8 n = 0;
  // don't just return nuContNum. we only want the number of actual gamepads ignoring special input devices.
  for(i = 0; i < NU_CONT_MAXCONTROLLERS; ++i)
  {
    if(xo_contoller_IsConnected(i))
    {
      n++;
    }
  }
  return n;
}

u8 xo_controller_GetIndex(u8 nthController)
{
  u8 i; // actual index
  u8 n; // valid controller index
  for(i=0,n=0; i < NU_CONT_MAXCONTROLLERS; ++i) {
    if(xo_contoller_IsConnected(i))
    {
      if(n == nthController)
      {
        return i;
      }
      n++;
    }
  }
  return 0xff;
}

u16 xo_controller_ButtonDown(u8 index, Button_t button)
{
  return s_ControllersCurrent[index].button & (u16)button;
}

u16 xo_controller_ButtonUp(u8 index, Button_t button)
{
  return !xo_controller_ButtonDown(index, button);
}

u16 xo_controller_ButtonPressed(u8 index, Button_t button)
{
  return xo_controller_ButtonDown(index, button) && !(s_ControllersLast[index].button & (u16)button);
}

u16 xo_controller_ButtonReleased(u8 index, Button_t button)
{
  return xo_controller_ButtonUp(index, button) && (s_ControllersLast[index].button & (u16)button);
}

void xo_controller_GetAxisUnclamped(u8 index, Axis_t axis, f32 *xOut, f32 *yOut)
{
  f32 x = 0.f, y = 0.f;
  switch (axis)
  {
  case XO_AXIS_STICK:
    // raw to float
    x = (f32)s_ControllersCurrent[index].stick_x;
    y = (f32)s_ControllersCurrent[index].stick_y;
    // clamp -80 to 80
    x = x < -80.f ? -80.f : (x > 80.f ? 80.f : x);
    y = y < -80.f ? -80.f : (y > 80.f ? 80.f : y);
    // 0 to 160
    x += 80.f;
    y += 80.f;
    // 0 to 1
    x /= 160.f;
    y /= 160.f;
    // 0 to 2
    x *= 2.f;
    y *= 2.f;
    // -1 to 1
    x -= 1.f;
    y -= 1.f;
    break;
  case XO_AXIS_DPAD:
    if (xo_controller_ButtonDown(index, XO_BUTTON_D_DOWN))
    {
      y -= 1.f;
    }
    if (xo_controller_ButtonDown(index, XO_BUTTON_D_UP))
    {
      y += 1.f;
    }
    if (xo_controller_ButtonDown(index, XO_BUTTON_D_LEFT))
    {
      x -= 1.f;
    }
    if (xo_controller_ButtonDown(index, XO_BUTTON_D_RIGHT))
    {
      x += 1.f;
    }
    break;
  case XO_AXIS_CPAD:
    if (xo_controller_ButtonDown(index, XO_BUTTON_C_DOWN))
    {
      y -= 1.f;
    }
    if (xo_controller_ButtonDown(index, XO_BUTTON_C_UP))
    {
      y += 1.f;
    }
    if (xo_controller_ButtonDown(index, XO_BUTTON_C_LEFT))
    {
      x -= 1.f;
    }
    if (xo_controller_ButtonDown(index, XO_BUTTON_C_RIGHT))
    {
      x += 1.f;
    }
    break;
  }
  *xOut = x;
  *yOut = y;
}

void xo_controller_GetAxisClamped(u8 index, Axis_t axis, f32 *xOut, f32 *yOut)
{
  f32 mag;
  xo_controller_GetAxisUnclamped(index, axis, xOut, yOut);
  mag = xo_math_magnitude2d(*xOut, *yOut);
  if (mag > 1.f)
  {
    *xOut /= mag;
    *yOut /= mag;
  }
}