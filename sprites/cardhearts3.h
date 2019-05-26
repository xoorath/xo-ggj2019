// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: cardhearts3
// Size: 64 x 87
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _cardhearts3_H_
#define _cardhearts3_H_

#include <xo-types.h>
#include <xo-img.h>

#include <xo-spec.h>

xo_spec_DeclareRomSegment(cardhearts3)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t cardhearts3;
#else // GENERATED_IMAGE_DECLARATIONS
#include <xo-render.h>
#include <PR/gbi.h>

Vtx cardhearts3_mesh_0[] = {
    {.v = {.ob = {0  , 0  , 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , 0  , 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -32, 0}, .flag = 0, .tc = {64 <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -32, 0}, .flag = 0, .tc = {0  <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardhearts3_mesh_0

Vtx cardhearts3_mesh_1[] = {
    {.v = {.ob = {0  , -32, 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -32, 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -64, 0}, .flag = 0, .tc = {64 <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -64, 0}, .flag = 0, .tc = {0  <<6, 32 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardhearts3_mesh_1

Vtx cardhearts3_mesh_2[] = {
    {.v = {.ob = {0  , -64, 0}, .flag = 0, .tc = {0  <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -64, 0}, .flag = 0, .tc = {64 <<6, 0  <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {64 , -87, 0}, .flag = 0, .tc = {64 <<6, 23 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {0  , -87, 0}, .flag = 0, .tc = {0  <<6, 23 <<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardhearts3_mesh_2

ImgSeg_t cardhearts3_components[] = {
  {
    _cardhearts3SegmentRomStart + 0,
    _cardhearts3SegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardhearts3_mesh_0
  },
  {
    _cardhearts3SegmentRomStart + 4096,
    _cardhearts3SegmentRomStart + 8192,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardhearts3_mesh_1
  },
  {
    _cardhearts3SegmentRomStart + 8192,
    _cardhearts3SegmentRomStart + 11136,
    64, 23,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardhearts3_mesh_2
  }
}; // cardhearts3_components

Img_t cardhearts3 = {
  sizeof(cardhearts3_components)/sizeof(cardhearts3_components[0]),
  cardhearts3_components,
  64, 87,

  G_TF_BILERP
}; // cardhearts3

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _cardhearts3_H_
