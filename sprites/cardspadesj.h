// Generated by xo-tt64.
// A tool by xoorath.
//
// Name: cardspadesj
// Size: 64 x 87
// Type: 16-Bit RGBA (OUTFMT_RGBA_16)

#ifndef _cardspadesj_H_
#define _cardspadesj_H_

#include <PR/ultratypes.h>
#include <xo-img.h>

#include "xo-spec.h"

xo_spec_DeclareRomSegment(cardspadesj)

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t cardspadesj;
#else // GENERATED_IMAGE_DECLARATIONS
#include "xo-render.h"
#include <PR/gbi.h>

Vtx cardspadesj_mesh_0[] = {
    {.v = {.ob = {  0,   0, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64,   0, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -32, 0}, .flag = 0, .tc = { 64<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -32, 0}, .flag = 0, .tc = {  0<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardspadesj_mesh_0

Vtx cardspadesj_mesh_1[] = {
    {.v = {.ob = {  0, -32, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -32, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -64, 0}, .flag = 0, .tc = { 64<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -64, 0}, .flag = 0, .tc = {  0<<6,  32<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardspadesj_mesh_1

Vtx cardspadesj_mesh_2[] = {
    {.v = {.ob = {  0, -64, 0}, .flag = 0, .tc = {  0<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -64, 0}, .flag = 0, .tc = { 64<<6,   0<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = { 64, -87, 0}, .flag = 0, .tc = { 64<<6,  23<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}},
    {.v = {.ob = {  0, -87, 0}, .flag = 0, .tc = {  0<<6,  23<<6}, .cn = {0xff, 0xff, 0xff, 0xff}}}
}; // cardspadesj_mesh_2

ImgSeg_t cardspadesj_components[] = {
  {
    _cardspadesjSegmentRomStart + 0,
    _cardspadesjSegmentRomStart + 4096,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardspadesj_mesh_0
  },
  {
    _cardspadesjSegmentRomStart + 4096,
    _cardspadesjSegmentRomStart + 8192,
    64, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardspadesj_mesh_1
  },
  {
    _cardspadesjSegmentRomStart + 8192,
    _cardspadesjSegmentRomStart + 11136,
    64, 23,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
    NULL,
    cardspadesj_mesh_2
  }
}; // cardspadesj_components

Img_t cardspadesj = {
  sizeof(cardspadesj_components)/sizeof(cardspadesj_components[0]),
  cardspadesj_components,
  64, 87,

  G_TF_BILERP
}; // cardspadesj

#endif // GENERATED_IMAGE_DECLARATIONS

#endif // _cardspadesj_H_
