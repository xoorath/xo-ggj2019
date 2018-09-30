#include "donsol-audio.h"
#include <nusys.h>
#include <nualsgi_n.h>

void donsol_audio_Init(void)
{
  // Register the bank to the sequence player
  nuAuSeqPlayerBankSet(_midibankSegmentRomStart,
                       _midibankSegmentRomEnd - _midibankSegmentRomStart,
                       _miditableSegmentRomStart);

  // Register MIDI sequence data to the sequence player
  nuAuSeqPlayerSeqSet(_seqSegmentRomStart);

  // Register the bank to the sound player
  nuAuSndPlayerBankSet(_sfxbankSegmentRomStart,
                       _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart,
                       _sfxtableSegmentRomStart);
}

void donsol_audio_PlayMainSong(void)
{
  nuAuSeqPlayerSetNo(0, 0);
  nuAuSeqPlayerPlay(0);
}