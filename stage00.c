/*
   stage00.c

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "xo-render.h"

static float triPos_x; /* The display position, X */
static float triPos_y; /* The display position, Y */
static float theta;  /* The rotational angle of the square  */
static Transformation_t parentSquare, childSquare, grandchildSquare;

void shadetri();

/* The initialization of stage 0  */
void initStage00(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
  theta = 0.0;
}

void makeDL00(void)
{
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  {
    xo_render_Translate(&parentSquare, triPos_x, triPos_y, 0.0F);
    xo_render_Rotate(&parentSquare, theta, 0.0F, 0.0F, 1.0F);
    xo_render_BeginDraw(&parentSquare);
    shadetri();
    {
      xo_render_Translate(&childSquare, 25.f, 0.0f, 0.0F);
      xo_render_Rotate(&childSquare, theta, 0.0F, 0.0F, 1.0F);
      xo_render_BeginDraw(&childSquare);
      shadetri();
      {
        xo_render_Translate(&grandchildSquare, 2.5f, 0.0f, 0.0F);
        xo_render_Rotate(&grandchildSquare, theta, 0.0F, 0.0F, 1.0F);
        xo_render_BeginDraw(&grandchildSquare);
        shadetri();
        xo_render_EndDraw();
      }
      xo_render_EndDraw();
    }
    xo_render_EndDraw();
  }

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("stage 00");
  xo_render_EndFrame();
}

/* The game progressing process for stage 0 */
void updateGame00(void)
{
  static float vel = 1.0;

  /* Data reading of controller 1  */
  nuContDataGetEx(contdata,0);

  /* Change the display position according to stick data  */
  triPos_x = contdata->stick_x;
  triPos_y = contdata->stick_y;

  /* The reverse rotation by the A button  */
  if(contdata[0].trigger & A_BUTTON)
    vel = -vel;

  /* Rotate fast while the B button is pushed  */
  if(contdata[0].button & B_BUTTON)
    theta += vel * 3.0;
  else
    theta += vel;

  /* Change the pending check when the Z button is pushed  */
  if(contdata[0].trigger & Z_TRIG)
    pendflag ^= 1;


  /* Move to stage 1 when the start button is pushed  */
  if(contdata[0].trigger & START_BUTTON){
    /* Remove the call-back function. */
    nuGfxFuncRemove();
    /* Specify next stage to main  */
    stage = 1;
  }
}

/* The vertex coordinate  */
static Vtx shade_vtx[] =  {
        {        -64,  64, -5, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         64,  64, -5, 0, 0, 0, 0, 0, 0, 0xff	},
        {         64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff	},
};

/* Draw a square  */
void shadetri()
{
  int i;

  gSPVertex(g_Glist++,&(shade_vtx[0]),4, 0);

  gDPPipeSync(g_Glist++);
  gDPSetCycleType(g_Glist++,G_CYC_1CYCLE);
  gDPSetRenderMode(g_Glist++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(g_Glist++,0xFFFFFFFF);
  gSPSetGeometryMode(g_Glist++,G_SHADE| G_SHADING_SMOOTH);

  gSP2Triangles(g_Glist++,0,1,2,0,0,2,3,0);
}
