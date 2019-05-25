#ifndef __XO_AUDIO_H_
#define __XO_AUDIO_H_

#include <xo-types.h>

typedef struct {
  u8* songStart;
  u8* songEnd;
} Song_t;

typedef struct {
  u8* bankPtrStart;
  u8* bankPtrEnd;

  u8* bankStart;
  u8* bankEnd;

  u8* sfxStart;
  u8* sfxEnd;

  Song_t* songs;
  size_t songCount;

} AudioCtx_t;

typedef u8 Bark_t;

void xo_audio_Init(void);

void xo_audio_SetCtx(AudioCtx_t* ctx);
void xo_audio_PlaySong(AudioCtx_t* ctx, size_t track);
void xo_audio_PlayBark(AudioCtx_t* ctx, Bark_t bark);

#endif