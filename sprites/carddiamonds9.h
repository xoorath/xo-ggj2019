// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: carddiamonds9
// Size: 64 x 87
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _carddiamonds9_H_
#define _carddiamonds9_H_

#include <PR/ultratypes.h>
#include <xo-img.h>

#include "xo-spec.h"

xo_spec_DeclareRomSegment(carddiamonds9)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t carddiamonds9;
#else // GENERATED_IMAGE_DECLARATIONS
#include "xo-render.h"
#include <PR/gbi.h>

Vtx carddiamonds9_mesh_0[] = {
    {.v = {.ob = {  0,   0, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64,   0, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -32, 0}, .flag = 0, .tc = { 64<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -32, 0}, .flag = 0, .tc = {  0<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // carddiamonds9_mesh_0

Vtx carddiamonds9_mesh_1[] = {
    {.v = {.ob = {  0, -32, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -32, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -64, 0}, .flag = 0, .tc = { 64<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -64, 0}, .flag = 0, .tc = {  0<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // carddiamonds9_mesh_1

Vtx carddiamonds9_mesh_2[] = {
    {.v = {.ob = {  0, -64, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -64, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -87, 0}, .flag = 0, .tc = { 64<<6,  23<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -87, 0}, .flag = 0, .tc = {  0<<6,  23<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // carddiamonds9_mesh_2

ImgSeg_t carddiamonds9_components[] = {
  {
    _carddiamonds9SegmentRomStart + 0,
    _carddiamonds9SegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    carddiamonds9_mesh_0
  },
  {
    _carddiamonds9SegmentRomStart + 4096,
    _carddiamonds9SegmentRomStart + 8192,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    carddiamonds9_mesh_1
  },
  {
    _carddiamonds9SegmentRomStart + 8192,
    _carddiamonds9SegmentRomStart + 11136,
    64, 23,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    carddiamonds9_mesh_2
  }
}; // carddiamonds9_components

Img_t carddiamonds9 = {
  sizeof(carddiamonds9_components)/sizeof(carddiamonds9_components[0]),
  carddiamonds9_components,
  64, 87,

  G_TF_BILERP
}; // carddiamonds9

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _carddiamonds9_H_
