#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "render.h"

static float theta;  /* The rotational angle of the square */
static float triPos_x; /* The display position-X */
static float triPos_y; /* The display position-Y */

static Vtx squareVerts[] =  {
        { -64,  64, -5, 0, 0, 0, 0,    0xff, 0,    0xff},
        {  64,  64, -5, 0, 0, 0, 0,    0,    0,    0xff},
        {  64, -64, -5, 0, 0, 0, 0,    0,    0xff, 0xff},
        { -64, -64, -5, 0, 0, 0, 0xff, 0,    0,    0xff},
};

static u16 squareIndicies[] = {
  0,1,2,0,2,3
};

static Mesh_t squareMesh = {
  .vtxCount = sizeof(squareVerts)/sizeof(*squareVerts),
  .vtx = &squareVerts,
  .idxCount = sizeof(squareIndicies)/sizeof(*squareIndicies),
  .idx = &squareIndicies,
};

/* The initialization of stage 0 */
void initStage00(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
  theta = 0.0;
}

/* Make the display list and activate the task */
void makeDL00(void)
{
  { Render_BeginFrame(); 
  
    // try doing this for all render states on init.
    guOrtho(&g_RenderState->projection,
      -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
      -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
      1.0F, 10.0F, 1.0F);

    guRotate(&g_RenderState->modeling, theta, 0.0F, 0.0F, 1.0F);
    guTranslate(&g_RenderState->translate, triPos_x, triPos_y, 0.0F);

    { Render_BeginDraw();

      Render_MeshDefault(&squareMesh);

    } Render_EndDraw();
  } Render_EndFrame();
}


/* The game progressing process for stage 0 */
void updateGame00(void)
{  
  static float vel = 1.0;

  /* Data reading of controller 1 */
  nuContDataGetEx(contdata,0);

  /* Change the display position by stick data */
  triPos_x = contdata->stick_x;
  triPos_y = contdata->stick_y;

  /* The reverse rotation by the A button */
  if(contdata[0].trigger & A_BUTTON)
    {
      vel = -vel;
      osSyncPrintf("A button Push\n");
    }

  /* Rotate fast while pushing the B button */
  if(contdata[0].button & B_BUTTON)
    theta += vel * 3.0;
  else
    theta += vel;

  if(theta>360.0)
      theta-=360.0;
  else if (theta<0.0)
      theta+=360.0;

}