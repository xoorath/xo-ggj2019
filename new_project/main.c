/*
   main.c

   NuSYSTEM sample nu5

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.			
*/

#include <nusys.h>
#include <nualsgi_n.h>
#include "main.h"
#include "segment.h"

/* The stage number */
volatile int stage;

/* Declaration of the prototype */
void stage00(int);
void setAudioData(void);

/* Declaration of the external function */
void initStage00(void);
void makeDL00(void);
void updateGame00(void);

NUContData	contdata[1]; /* Read data of 1 controller */
/* Values 0 or 1 used by pending check of the call-back function */
volatile int pendflag = 0;
static int oldpendflag = 1;
/* Frame buffer (2 frame buffers) */
static u16*	FrameBuf2[2] = {
    (u16*)NU_GFX_FRAMEBUFFER1_ADDR,
    (u16*)NU_GFX_FRAMEBUFFER2_ADDR,
};
/* Frame buffer (3 frame buffers) */
static u16*	FrameBuf3[3] = {
    (u16*)NU_GFX_FRAMEBUFFER0_ADDR,
    (u16*)NU_GFX_FRAMEBUFFER1_ADDR,
    (u16*)NU_GFX_FRAMEBUFFER2_ADDR,
};
/* The number of displaying scene in a second */
int dspcount = 0;
/* The buffer for the console display */
char conbuf[40];

/*------------------------
	Main
--------------------------*/
void mainproc(void)
{
  /* The initialization of graphic */
  nuGfxInit();

  /* The initialization of the controller manager */
  nuContInit();
	
  /* The initializatio of audio */
  //nuAuInit();
  /* Register audio data on ROM */
  //setAudioData();
//
  //nuAuSeqPlayerSetNo(0,0);
  //nuAuSeqPlayerPlay(0);

  /* Set the stage number to 0 */
  stage = 0;

  while(1)
    {
      switch(stage)
	{
	  /* 
	     Register the corresponding call-back function according to the 
		 stage number. 
	     The call-back function sets the value to the stage when another    	     call-back function needs the register change.
	     */
	case 0:
	  /* Set the stage value to -1 first to wait for that the call-back 
	     function sets the value stage */
	  stage = -1;
	  /* The initialization of stage 0 */
	  initStage00();
	  /* Call-back register */
	  nuGfxFuncSet((NUGfxFunc)stage00);
	  /* Start to display */
	  nuGfxDisplayOn();
	  break;
	default:
	  break;
	}
      
      /* Wait for that the call-back function switches values (switch the 
	  scene) */
      while(stage == -1)
	;
      /* Clear the display */
      nuGfxDisplayOff();
    }
}

/* Set audio data */
void setAudioData(void)
{
  /* Register the bank to the sequence player */
  nuAuSeqPlayerBankSet(_midibankSegmentRomStart,
		       _midibankSegmentRomEnd - _midibankSegmentRomStart,
		       _miditableSegmentRomStart);
  /* Register MIDI sequence data to the sequence player */
  nuAuSeqPlayerSeqSet(_seqSegmentRomStart);
  /* Register the bank to the sound player */
  nuAuSndPlayerBankSet(_sfxbankSegmentRomStart,
		       _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart,
		       _sfxtableSegmentRomStart);
}


/*-----------------------------------------------------------------------------
  The call-back function 

  pindingGfx which is passed from Nusystem as the argument of the call-back 
  function is the total number of RCP tasks that are currently processing 
  and waiting for the process.
-----------------------------------------------------------------------------*/

/* The variable for counting how many scenes can be displayed in a second */
int calcFrame(void)
{
  static char frame[60];
  static int ptr = 0;
  static s64 prev = 0,now;
  int i,ctr;

  now = nuScRetraceCounter;
  if(prev >= now)
    now += 0x100000000LL;
  if(now - prev > 60)
    prev = now;
  while(prev < now-1)
    {
      frame[ptr++] = 0;
      ptr = ptr % 60;
      prev++;
    }
  frame[ptr++] = 1;
  ptr = ptr % 60;
  prev = now & 0xFFFFFFFF;
  ctr = 0;
  for(i = 0; i < 60; i++)
    ctr += frame[i];
  return(ctr);
}

/*
  Change function of frame buffer number 
*/
void changeFrameBuffer(void)
{
    if(pendflag)
	nuGfxSetCfb(FrameBuf3, 3);
    else
	nuGfxSetCfb(FrameBuf2, 2);
    oldpendflag = pendflag; /* End of updating */
}

/* The stage 0 */
void stage00(int pendingGfx)
{
  /* If necessary, change frame buffer number.*/
  if(pendflag != oldpendflag)
  {
    if(pendingGfx == 0) /* No pending display list */
      changeFrameBuffer();
    return; /* Do not launch a new task when this routine is in use */
  }

  /* Displaying process, depending on the number of processing/pending RCP tasks */
  if(pendingGfx < 4) /* The number of DLs used in stage00 is 3 kinds x 2 buffers */
    {
      dspcount = calcFrame();
      makeDL00();
    }

  /* The game progressing process */
  updateGame00(); 
}