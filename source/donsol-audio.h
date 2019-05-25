#ifndef __DONSOL_AUDIO_H_
#define __DONSOL_AUDIO_H_

#include <xo-audio.h>
#include <xo-spec.h>

xo_spec_DeclareCodeSegment();

// (*.wbk) bank containing sound data
// (*.ptr) pointer to bank sounds

xo_spec_DeclareRomSegment(donsolptr);   // gamesnd.ptr
xo_spec_DeclareRomSegment(donsolwbank); // gamesnd.wbk
xo_spec_DeclareRomSegment(donsolbin); // ambient.bin
xo_spec_DeclareRomSegment(donsolbfx); //gamsnd.bfx

xo_spec_DeclareRomSegment(countptr);
xo_spec_DeclareRomSegment(countwbank);
xo_spec_DeclareRomSegment(countbin);

// xo_spec_DeclareRomSegment(compbankPtr) // bank ptrs
// xo_spec_DeclareRomSegment(compankWbk) // sound bank data
// xo_spec_DeclareRomSegment(compankBin) // song1 midi
// xo_spec_DeclareRomSegment(compankBfx) // sfx list

// xo_spec_DeclareRomSegment(seq);         // midi.sbk
// xo_spec_DeclareRomSegment(midibank);    // wave.ctl
// xo_spec_DeclareRomSegment(miditable);   // wave.tbl
// xo_spec_DeclareRomSegment(sfxbank);     // se.ctl
// xo_spec_DeclareRomSegment(sfxtable);    // se.tbl

void donsol_audio_Init(void);

void donsol_audio_PlayMainSong(void);
void donsol_audio_BarkClick(u8 idx); // index is 0-3
void donsol_audio_BarkDenied(void);
void donsol_audio_BarkDone(void);
void donsol_audio_BarkFlip(void);

#endif // __DONSOL_AUDIO_H_