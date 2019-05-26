// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: cardhearts8
// Size: 64 x 87
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _cardhearts8_H_
#define _cardhearts8_H_

#include <xo-types.h>
#include <xo-img.h>

#include <xo-spec.h>

xo_spec_DeclareRomSegment(cardhearts8)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t cardhearts8;
#else // GENERATED_IMAGE_DECLARATIONS
#include <xo-render.h>
#include <PR/gbi.h>

Vtx cardhearts8_mesh_0[] = {
    {.v = {.ob = {0  , 0  , 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , 0  , 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -32, 0}, .flag = 0, .tc = {64 <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -32, 0}, .flag = 0, .tc = {0  <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardhearts8_mesh_0

Vtx cardhearts8_mesh_1[] = {
    {.v = {.ob = {0  , -32, 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -32, 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -64, 0}, .flag = 0, .tc = {64 <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -64, 0}, .flag = 0, .tc = {0  <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardhearts8_mesh_1

Vtx cardhearts8_mesh_2[] = {
    {.v = {.ob = {0  , -64, 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -64, 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -87, 0}, .flag = 0, .tc = {64 <<6, 23 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -87, 0}, .flag = 0, .tc = {0  <<6, 23 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardhearts8_mesh_2

ImgSeg_t cardhearts8_components[] = {
  {
    _cardhearts8SegmentRomStart + 0,
    _cardhearts8SegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardhearts8_mesh_0
  },
  {
    _cardhearts8SegmentRomStart + 4096,
    _cardhearts8SegmentRomStart + 8192,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardhearts8_mesh_1
  },
  {
    _cardhearts8SegmentRomStart + 8192,
    _cardhearts8SegmentRomStart + 11136,
    64, 23,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardhearts8_mesh_2
  }
}; // cardhearts8_components

Img_t cardhearts8 = {
  sizeof(cardhearts8_components)/sizeof(cardhearts8_components[0]),
  cardhearts8_components,
  64, 87,

  G_TF_BILERP
}; // cardhearts8

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _cardhearts8_H_
