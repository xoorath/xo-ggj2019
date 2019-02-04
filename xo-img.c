#include "xo-img.h"

#include "xo-render.h"
#include "img-donsol-heart-ace.h"

#include <nusys.h>

char g_TextureBuffer[1024*4*32] = {0};
// todo: use linear allocator with block management
char* g_CurrentTexture = &g_TextureBuffer[0];

// todo: centralize rom2ram functions
void iRom2Ram(void *from_addr, void *to_addr, s32 seq_size, s32 lim)
{
  // Cannot transfer if size is an odd number, so make it even
  if (seq_size & 0x00000001)
    seq_size++;

  nuPiReadRom((u32)from_addr, to_addr, seq_size >= lim ? lim : seq_size);
}

void xo_img_Load(Img_t *img) {
  u16 i;
  s32 segSize;
  ImgSeg_t* seg;

  if(img == NULL) {
    return;
  }
  // todo: malloc one big block and distribute it.
  for(i = 0; i < img->componentCount; ++i) {
    seg = &img->components[i];
    if(seg->data == NULL) {
      segSize = (seg->w * seg->h * 2) + 8;
      seg->data = g_CurrentTexture;
      g_CurrentTexture += segSize;
      nuPiReadRom((u32)seg->start, seg->data, segSize);
    }
  }
}

void xo_img_Unload(Img_t *img) {
  u16 i;
  ImgSeg_t* seg;

  if(img == NULL) {
    return;
  }
  // todo: once we malloc one big block and distribute it,
  // free the first block but null all blocks.
  for(i = 0; i < img->componentCount; ++i) {
    seg = &img->components[i];
    if(seg->data != NULL) {
      //free(seg->data);
      seg->data = NULL;
    }
  }
}

void xo_img_Bind(Img_t *img, u8 segment)
{
  ImgSeg_t* seg;
  s32 segSize;
  if(img != NULL) {
    seg = &img->components[segment];

    //segSize = (seg->end - seg->start);
    //seg->data = textureData[segment];
    //iRom2Ram(seg->start, seg->data, segSize, segSize);


    gDPSetColorDither(g_Glist++,G_CD_ENABLE);
    //gDPSetTexturePersp(g_Glist++,G_TP_PERSP);
    //gDPSetTextureLOD(g_Glist++,G_TL_TILE);
    //gDPSetTextureConvert(g_Glist++,G_TC_FILT);
    //gDPSetTextureLUT(g_Glist++,G_TT_NONE);

#ifndef __INTELLISENSE__
    gDPSetCombineMode(g_Glist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
#endif
    gDPSetTextureFilter(g_Glist++, img->filter);
    gSPTexture(g_Glist++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
  } else {
    xo_img_Unbind();
  }
}

void xo_img_Unbind(void)
{
#ifndef __INTELLISENSE__
  gDPSetCombineMode(g_Glist++, G_CC_SHADE, G_CC_SHADE);
#endif
  gSPTexture(g_Glist++,0, 0, 0, 0, G_OFF);
}

void xo_img_Apply(Img_t* img, u8 segment)
{
  ImgSeg_t* seg = &img->components[segment];
  if(seg->data) {
    gDPLoadTextureBlock(g_Glist++,
      &((char*)seg->data)[8/*magic, if coming from rom*/],
      G_IM_FMT_RGBA,
      G_IM_SIZ_16b,
      seg->w, seg->h, 0,
      seg->txSettingU, // G_TX_CLAMP | G_TX_NOMIRROR
      seg->txSettingV, // G_TX_CLAMP | G_TX_NOMIRROR
      G_TX_NOMASK, G_TX_NOMASK,
      G_TX_NOLOD, G_TX_NOLOD);
  }
}