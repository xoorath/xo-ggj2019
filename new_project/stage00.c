/*
   stage00.c 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.	
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "render.h"

static float triPos_x; /* The display position, X */
static float triPos_y; /* The display position, Y */
static float theta;  /* The rotational angle of the square  */

/* The vertex coordinate  */
static Vtx shade_vtx[] =  {
        {        -64,  64, -5, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         64,  64, -5, 0, 0, 0, 0, 0, 0, 0xff	},
        {         64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff	},
};

static u16 squareIndicies[] = {0,1,2, 2,3,0};

static Mesh_t squareMesh = {
  .vtx = shade_vtx,
  .vtxCount = sizeof(shade_vtx)/sizeof(*shade_vtx),
  .idx = squareIndicies,
  .idxCount = sizeof(squareIndicies)/sizeof(*squareIndicies)
}

/* The initialization of stage 0  */
void initStage00(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
  theta = 0.0;
}

/* Make the display list and activate the task  */
void makeDL00(void)
{
  { Render_BeginFrame(); 
  
    guTranslate(&g_RenderData->translation, triPos_x, triPos_y, 0.0F);
    guRotate(&g_RenderData->rotation, theta, 0.0F, 0.0F, 1.0F);

    { Render_BeginDraw();
      Render_SetCycleInfo(&g_DefaultCycleInfo);
      Render_SetGeometryMode(G_SHADE | G_SHADING_SMOOTH);
      Render_Mesh(&squareMesh);
    } Render_EndDraw();

    guTranslate(&g_RenderData->translation, triPos_x, triPos_y, 0.0F);
    guRotate(&g_RenderData->rotation, 0.f, 0.0F, 0.0F, 1.0F);
    
    { Render_BeginDraw();
      Render_SetCycleInfo(&g_DefaultCycleInfo);
      Render_SetGeometryMode(G_SHADE | G_SHADING_SMOOTH);
      Render_Mesh(&squareMesh);
    } Render_EndDraw();

  } Render_EndFrame();
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
}
