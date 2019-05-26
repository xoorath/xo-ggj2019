// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: cardclubsk_l
// Size: 64 x 32
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _cardclubsk_l_H_
#define _cardclubsk_l_H_

#include <xo-types.h>
#include <xo-img.h>

#include <xo-spec.h>

xo_spec_DeclareRomSegment(cardclubsk_l)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t cardclubsk_l;
#else // GENERATED_IMAGE_DECLARATIONS
#include <xo-render.h>
#include <PR/gbi.h>

Vtx cardclubsk_l_mesh_0[] = {
    {.v = {.ob = {0  , 0  , 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , 0  , 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -32, 0}, .flag = 0, .tc = {64 <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -32, 0}, .flag = 0, .tc = {0  <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardclubsk_l_mesh_0

ImgSeg_t cardclubsk_l_components[] = {
  {
    _cardclubsk_lSegmentRomStart + 0,
    _cardclubsk_lSegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardclubsk_l_mesh_0
  }
}; // cardclubsk_l_components

Img_t cardclubsk_l = {
  sizeof(cardclubsk_l_components)/sizeof(cardclubsk_l_components[0]),
  cardclubsk_l_components,
  64, 32,

  G_TF_BILERP
}; // cardclubsk_l

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _cardclubsk_l_H_
