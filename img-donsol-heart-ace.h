#ifndef Heart_Ace_header
#define Heart_Ace_header

#include <PR/ultratypes.h>
#include <xo-img.h>

#include "xo-spec.h"

xo_spec_DeclareRomSegment(heartace);

#ifndef GENERATED_IMAGE_DECLARATIONS
extern Img_t img_donsol_heart_ace;
#else
#include "xo-render.h"
ImgSeg_t heart_ace_components[] = {
  {
    _heartaceSegmentRomStart,
    _heartaceSegmentRomEnd,
    32, 32,
    G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR
  }
};

Img_t img_donsol_heart_ace = {
  sizeof(heart_ace_components)/sizeof(heart_ace_components[0]),
  heart_ace_components,

  G_TF_POINT
};
#endif

#endif