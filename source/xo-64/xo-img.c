#include <xo-img.h>

#include <xo-alloc.h>
#include <xo-buffer.h>
#include <xo-render.h>

#include <malloc.h>

#include <nusys.h>

static OSRegion region;
static BlockAllocator_t g_TextureAllocator1, g_TextureAllocator2;
//char g_TextureBuffer1[512000] = {0};
//char g_TextureBuffer2[512000] = {0};

// todo: centralize rom2ram functions
void iRom2Ram(void *from_addr, void *to_addr, s32 seq_size, s32 lim)
{
  nuPiReadRom((u32)from_addr, to_addr, seq_size >= lim ? lim : seq_size);
}

void xo_img_init(void) {
  //xo_alloc_init_allocator(&g_TextureAllocator1, malloc(512000), 512000);
  //xo_alloc_init_allocator(&g_TextureAllocator2, malloc(512000), 512000);
}

void xo_img_Load(Img_t *img) {
  u16 i;
  s32 segSize;
  ImgSeg_t* seg;

  if(NULL == img) {
    return;
  }
  for(i = 0; i < img->componentCount; ++i) {
    seg = &img->components[i];
    if(NULL == seg->data) {
      segSize = (seg->w * seg->h * 2);

      seg->data = malloc(segSize);

      if(NULL != seg->data) {
        nuPiReadRom((u32)seg->start, seg->data, segSize);
      }
    }
  }
}

void xo_img_Unload(Img_t *img) {
  u16 i;
  ImgSeg_t* seg;

  if(NULL == img) {
    return;
  }
  for(i = 0; i < img->componentCount; ++i) {
    seg = &img->components[i];
    if(NULL != seg->data) {
        free(seg->data);

      seg->data = NULL;
    }
  }
}

void xo_img_Bind(Img_t *img, u8 segment)
{
  ImgSeg_t* seg;
  s32 segSize;
  if(NULL != img) {
    seg = &img->components[segment];

    //segSize = (seg->end - seg->start);
    //seg->data = textureData[segment];
    //iRom2Ram(seg->start, seg->data, segSize, segSize);


    gDPSetColorDither(g_Glist++,G_CD_DISABLE);
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
  if(NULL != seg->data) {
    gDPLoadTextureBlock(g_Glist++,
      seg->data,
      G_IM_FMT_RGBA,
      G_IM_SIZ_16b,
      seg->w, seg->h, 0,
      seg->txSettingU,
      seg->txSettingV,
      G_TX_NOMASK, G_TX_NOMASK,
      G_TX_NOLOD, G_TX_NOLOD);
  }
}

void xo_img_DebugDraw(void) {
  xo_alloc_dbg_draw(&g_TextureAllocator1, 0, 10);
  xo_alloc_dbg_draw(&g_TextureAllocator2, 0, 14);
}