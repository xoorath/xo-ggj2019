#include <xo-audio.h>
#include <ASSERT.H>

#include <nusys.h>
#include <nualstl_n.h>

#include <xo-spec.h>

int ptr_buf[NU_AU_SAMPLE_SIZE];
int tune_buf[NU_AU_SONG_SIZE];
int sfx_buf[NU_AU_SE_SIZE];
musHandle seqHandle = 0;

void Rom2Ram(void *from_addr, void *to_addr, s32 seq_size)
{
  // Cannot transfer if size is an odd number, so make it even
  if (seq_size & 0x00000001)
    seq_size++;

  nuPiReadRom((u32)from_addr, to_addr, seq_size);
}

void xo_audio_SetCtx(AudioCtx_t* ctx)
{
  u8
    *ptrStart,
    *ptrEnd,
    *bankStart,
    *sfxStart,
    *sfxEnd;

  ptrStart =  ctx->bankPtrStart;
  ptrEnd =    ctx->bankPtrEnd;
  bankStart = ctx->bankStart;
  sfxStart =  ctx->sfxStart;
  sfxEnd =    ctx->sfxEnd;

  if(ptrStart && ptrEnd)
  {
    assert(ptrStart != ptrEnd && ptrEnd > ptrStart);
    Rom2Ram((void *)ptrStart, (void *)ptr_buf, ptrEnd - ptrStart);
  }

  if(bankStart)
  {
    assert(ptrStart && ptrEnd); // we need a bank ptr to have been loaded.
    MusPtrBankInitialize((void *)ptr_buf, (void *)bankStart);
  }

  if(sfxStart && sfxEnd)
  {
    assert(sfxStart != sfxEnd && sfxEnd > sfxStart);
    Rom2Ram((void *)sfxStart, (void *)sfx_buf, sfxEnd - sfxStart);
    MusFxBankInitialize(sfx_buf);
  }
}

void xo_audio_PlaySong(AudioCtx_t* ctx, size_t track)
{
  u8
    *songStart,
    *songEnd;

  assert(track < ctx->songCount);

  songStart = ctx->songs[track].songStart;
  songEnd =   ctx->songs[track].songEnd;

  Rom2Ram((void *)songStart, (void *)tune_buf, songEnd - songStart);
  MusStartSong(tune_buf);
}

void xo_audio_PlayBark(AudioCtx_t* ctx, Bark_t bark)
{
  // todo
  MusStartEffect(bark);
}


void xo_audio_Init(void)
{
  musConfig c;

  c.control_flag = 0;                         // Set to MUSCONTROL_RAM if wbk file also placed in RAM
  c.channels = NU_AU_CHANNELS;                // Maximum total number of channels
  c.sched = NULL;                             // ?
  c.thread_priority = NU_AU_MGR_THREAD_PRI;   // thread priority (highest)
  c.heap = (unsigned char *)NU_AU_HEAP_ADDR;  // Heap address
  c.heap_length = NU_AU_HEAP_SIZE;            // Heap size
  c.ptr = NULL;                               // Allows you to set a default ptr file
  c.wbk = NULL;                               // Allows you to set a default wbk file
  c.default_fxbank = NULL;                    // Allows you to set a default bfx file
  c.fifo_length = NU_AU_FIFO_LENGTH;          // ?
  c.syn_updates = NU_AU_SYN_UPDATE_MAX;       // ?
  c.syn_output_rate = 44100;                  // Audio output rate. The higher, the better quality
  c.syn_rsp_cmds = NU_AU_CLIST_LEN;           // ?
  c.syn_retraceCount = 1;                     // ?
  c.syn_num_dma_bufs = NU_AU_DMA_BUFFER_NUM;  // ?
  c.syn_dma_buf_size = NU_AU_DMA_BUFFER_SIZE; // ?

  // Initialize the Audio Manager.
  nuAuStlMgrInit(&c);

  // Register the PRENMI function.
  nuAuPreNMIFuncSet(nuAuPreNMIProc);
}