#include "donsol-audio.h"
#include "gamesnd.h"
#include <nusys.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
Song_t donsolSongs[] = {
  {
    .songStart = _donsolbinSegmentRomStart,
    .songEnd = _donsolbinSegmentRomEnd
  }
};

AudioCtx_t donsolCtx = {
  .bankPtrStart = _donsolptrSegmentRomStart,
  .bankPtrEnd = _donsolptrSegmentRomEnd,

  .bankStart = _donsolwbankSegmentRomStart,
  .bankEnd = _donsolwbankSegmentRomEnd,

  .sfxStart = _donsolbfxSegmentRomStart,
  .sfxEnd = _donsolbfxSegmentRomEnd,

  .songCount = sizeof(donsolSongs)/sizeof(donsolSongs[0]),
  .songs = &donsolSongs[0]
};

////////////////////////////////////////////////////////////////////////////////////////////////////
Song_t countSongs[] = {
  {
    .songStart = _countbinSegmentRomStart,
    .songEnd = _countbinSegmentRomEnd
  }
};

AudioCtx_t countCtx = {
  .bankPtrStart = _countptrSegmentRomStart,
  .bankPtrEnd = _countptrSegmentRomEnd,

  .bankStart = _countwbankSegmentRomStart,
  .bankEnd = _countwbankSegmentRomEnd,

  .sfxStart = NULL,
  .sfxEnd = NULL,

  .songCount = sizeof(countSongs)/sizeof(countSongs[0]),
  .songs = &countSongs[0]
};

////////////////////////////////////////////////////////////////////////////////////////////////////

void donsol_audio_Init(void)
{
  xo_audio_SetCtx(&donsolCtx);
}

void donsol_audio_PlayMainSong(void)
{
  //xo_audio_PlaySong(&donsolCtx, 0);
  xo_audio_PlayBark(&donsolCtx, (Bark_t)FX_AMBIENT);
}

void donsol_audio_BarkClick(u8 idx)
{
  static Bark_t clickBarks[] = {
    (Bark_t)FX_CLICK1,
    (Bark_t)FX_CLICK2,
    (Bark_t)FX_CLICK3,
    (Bark_t)FX_CLICK4
  };
  xo_audio_PlayBark(&donsolCtx, clickBarks[idx % 4]);
}

void donsol_audio_BarkDenied(void)
{
  xo_audio_PlayBark(&donsolCtx, (Bark_t)FX_DENIED);
}

void donsol_audio_BarkDone(void)
{
  xo_audio_PlayBark(&donsolCtx, (Bark_t)FX_DONE);
}

void donsol_audio_BarkFlip(void)
{
  xo_audio_PlayBark(&donsolCtx, (Bark_t)FX_FLIP);
}