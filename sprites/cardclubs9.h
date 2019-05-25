// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: cardclubs9
// Size: 64 x 87
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _cardclubs9_H_
#define _cardclubs9_H_

#include <PR/ultratypes.h>
#include <xo-img.h>

#include <xo-spec.h>

xo_spec_DeclareRomSegment(cardclubs9)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t cardclubs9;
#else // GENERATED_IMAGE_DECLARATIONS
#include <xo-render.h>
#include <PR/gbi.h>

Vtx cardclubs9_mesh_0[] = {
    {.v = {.ob = {  0,   0, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64,   0, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -32, 0}, .flag = 0, .tc = { 64<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -32, 0}, .flag = 0, .tc = {  0<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardclubs9_mesh_0

Vtx cardclubs9_mesh_1[] = {
    {.v = {.ob = {  0, -32, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -32, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -64, 0}, .flag = 0, .tc = { 64<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -64, 0}, .flag = 0, .tc = {  0<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardclubs9_mesh_1

Vtx cardclubs9_mesh_2[] = {
    {.v = {.ob = {  0, -64, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -64, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -87, 0}, .flag = 0, .tc = { 64<<6,  23<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -87, 0}, .flag = 0, .tc = {  0<<6,  23<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardclubs9_mesh_2

ImgSeg_t cardclubs9_components[] = {
  {
    _cardclubs9SegmentRomStart + 0,
    _cardclubs9SegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardclubs9_mesh_0
  },
  {
    _cardclubs9SegmentRomStart + 4096,
    _cardclubs9SegmentRomStart + 8192,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardclubs9_mesh_1
  },
  {
    _cardclubs9SegmentRomStart + 8192,
    _cardclubs9SegmentRomStart + 11136,
    64, 23,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardclubs9_mesh_2
  }
}; // cardclubs9_components

Img_t cardclubs9 = {
  sizeof(cardclubs9_components)/sizeof(cardclubs9_components[0]),
  cardclubs9_components,
  64, 87,

  G_TF_BILERP
}; // cardclubs9

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _cardclubs9_H_
