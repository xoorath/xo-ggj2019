// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: cardclubs9_l
// Size: 64 x 32
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _cardclubs9_l_H_
#define _cardclubs9_l_H_

#include <xo-types.h>
#include <xo-img.h>

#include <xo-spec.h>

xo_spec_DeclareRomSegment(cardclubs9_l)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t cardclubs9_l;
#else // GENERATED_IMAGE_DECLARATIONS
#include <xo-render.h>
#include <PR/gbi.h>

Vtx cardclubs9_l_mesh_0[] = {
    {.v = {.ob = {0  , 0  , 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , 0  , 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -32, 0}, .flag = 0, .tc = {64 <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -32, 0}, .flag = 0, .tc = {0  <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardclubs9_l_mesh_0

ImgSeg_t cardclubs9_l_components[] = {
  {
    _cardclubs9_lSegmentRomStart + 0,
    _cardclubs9_lSegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardclubs9_l_mesh_0
  }
}; // cardclubs9_l_components

Img_t cardclubs9_l = {
  sizeof(cardclubs9_l_components)/sizeof(cardclubs9_l_components[0]),
  cardclubs9_l_components,
  64, 32,

  G_TF_BILERP
}; // cardclubs9_l

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _cardclubs9_l_H_
