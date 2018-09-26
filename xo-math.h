#ifndef __XO_MATH_H_
#define __XO_MATH_H_

#include <PR/ultratypes.h>
#include <MATH.H>

//////////////////////////////////////////////////////////////////////////////////////////
// Vector2
//////////////////////////////////////////////////////////////////////////////////////////

inline f32 xo_math_magnitude2d(f32 x, f32 y)
{
  return (f32)sqrt((f64)((x*x) + (y*y)));
}

inline void xo_math_normalize2d(f32 *x, f32 *y)
{
  f32 mag = xo_math_magnitude2d(*x, *y);
  if(mag != 0.f)
  {
    *x = *x / mag;
    *y = *y / mag;
  }
}

#endif