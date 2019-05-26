// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: carddiamonds2_l
// Size: 64 x 32
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _carddiamonds2_l_H_
#define _carddiamonds2_l_H_

#include <xo-types.h>
#include <xo-img.h>

#include <xo-spec.h>

xo_spec_DeclareRomSegment(carddiamonds2_l)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t carddiamonds2_l;
#else // GENERATED_IMAGE_DECLARATIONS
#include <xo-render.h>
#include <PR/gbi.h>

Vtx carddiamonds2_l_mesh_0[] = {
    {.v = {.ob = {0  , 0  , 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , 0  , 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -32, 0}, .flag = 0, .tc = {64 <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -32, 0}, .flag = 0, .tc = {0  <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // carddiamonds2_l_mesh_0

ImgSeg_t carddiamonds2_l_components[] = {
  {
    _carddiamonds2_lSegmentRomStart + 0,
    _carddiamonds2_lSegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    carddiamonds2_l_mesh_0
  }
}; // carddiamonds2_l_components

Img_t carddiamonds2_l = {
  sizeof(carddiamonds2_l_components)/sizeof(carddiamonds2_l_components[0]),
  carddiamonds2_l_components,
  64, 32,

  G_TF_BILERP
}; // carddiamonds2_l

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _carddiamonds2_l_H_
