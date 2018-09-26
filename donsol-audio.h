#ifndef __DONSOL_AUDIO_H_
#define __DONSOL_AUDIO_H_

#include "xo-spec.h"

xo_spec_DeclareRomSegment(seq);         // midi.sbk
xo_spec_DeclareRomSegment(midibank);    // wave.ctl
xo_spec_DeclareRomSegment(miditable);   // wave.tbl
xo_spec_DeclareRomSegment(sfxbank);     // se.ctl
xo_spec_DeclareRomSegment(sfxtable);    // se.tbl


void donsol_audio_Init(void);

void donsol_audio_PlayMainSong(void);

#endif // __DONSOL_AUDIO_H_