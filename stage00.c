#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "xo-img.h"
#include "xo-render.h"
#include "xo-controller.h"
#include "img-donsol-heart-ace.h"

static struct
{
  f32
      x, y;

  Transformation_t
      parentSquare,
      childSquare,
      grandchildSquare,
      cardTop,
      cardBottom;

  u8
    controllerPluggedIn;

  float theta;
} s_Stage00;

void BindMesh(Vtx*, u16);
void ApplyMesh(void);

/* The initialization of stage 0  */
void initStage00(void)
{
  s_Stage00.x = 0.0f;
  s_Stage00.y = 0.0f;
  s_Stage00.theta = 0.0f;
  // note: transformations are set before they're used. don't bother setting them here.
  s_Stage00.controllerPluggedIn = FALSE;
  donsol_audio_Init();
  donsol_audio_PlayMainSong();

  xo_img_Load(&heart_ace);
}

void makeDL00(void)
{
  xo_render_BeginFrame();

  xo_render_BeginDisplayList_Render();

  // if(0) {
  //   xo_render_Translate(&s_Stage00.parentSquare, s_Stage00.triPos_x, s_Stage00.triPos_y, 0.0F);
  //   xo_render_Rotate(&s_Stage00.parentSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
  //   xo_render_BeginDraw(&s_Stage00.parentSquare);
  //   xo_img_Bind(&heart_ace, 0);
  //   BindMesh();
  //   xo_img_Apply(&heart_ace, 0);
  //   ApplyMesh();
  //   xo_img_Bind(NULL, 0);
  //   {
  //     xo_render_Translate(&s_Stage00.childSquare, 25.f, 0.0f, 0.0F);
  //     xo_render_Rotate(&s_Stage00.childSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
  //     xo_render_BeginDraw(&s_Stage00.childSquare);
  //     xo_img_Bind(&heart_ace, 0);
  //     BindMesh();
  //     xo_img_Apply(&heart_ace, 0);
  //     ApplyMesh();
  //     xo_img_Bind(NULL, 0);
  //     {
  //       xo_render_Translate(&s_Stage00.grandchildSquare, 2.5f, 0.0f, 0.0F);
  //       xo_render_Rotate(&s_Stage00.grandchildSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
  //       xo_render_BeginDraw(&s_Stage00.grandchildSquare);
  //       BindMesh();
  //       ApplyMesh();
  //       xo_render_EndDraw();
  //     }
  //     xo_render_EndDraw();
  //   }
  //   xo_render_EndDraw();
  // }

  {
    xo_render_Translate(&s_Stage00.grandchildSquare, (int)s_Stage00.x, (int)s_Stage00.y, 0.0F);
    xo_render_Rotate(&s_Stage00.grandchildSquare, s_Stage00.theta, 0.0F, 0.0F, 1.0F);
    xo_render_BeginDraw(&s_Stage00.grandchildSquare);


    // whole thing:
    // 64 x 92
    // each part:
    // 64, 32,
    // 64, 32,
    // 64, 28

    // center: 32, 46

    {
      xo_render_Translate(&s_Stage00.parentSquare, 0.0f, 28.f + 32.f + 16.f - 46.f, 0.0F);
      xo_render_Rotate(&s_Stage00.parentSquare, 0.0f, 0.0F, 0.0F, 1.0F);
      xo_render_BeginDraw(&s_Stage00.parentSquare);
      xo_img_Bind(&heart_ace, 0);
      BindMesh(heart_ace.components[0].mesh, 4);
      xo_img_Apply(&heart_ace, 0);
      ApplyMesh();
      xo_img_Bind(NULL, 0);
      xo_render_EndDraw();
    }

    {
      xo_render_Translate(&s_Stage00.cardTop, 0.0f, 28.f + 16.f - 46.f, 0.0F);
      xo_render_Rotate(&s_Stage00.cardTop, 0.0f, 0.0F, 0.0F, 1.0F);
      xo_render_BeginDraw(&s_Stage00.cardTop);
      xo_img_Bind(&heart_ace, 1);
      BindMesh(heart_ace.components[1].mesh, 4);
      xo_img_Apply(&heart_ace, 1);
      ApplyMesh();
      xo_img_Bind(NULL, 0);
      xo_render_EndDraw();
    }

    {
      xo_render_Translate(&s_Stage00.childSquare, 0.0f, 14.0f - 46.f, 0.0F);
      xo_render_Rotate(&s_Stage00.childSquare, 0.0f, 0.0F, 0.0F, 1.0F);
      xo_render_BeginDraw(&s_Stage00.childSquare);
      xo_img_Bind(&heart_ace, 2);
      BindMesh(heart_ace.components[2].mesh, 4);
      xo_img_Apply(&heart_ace, 2);
      ApplyMesh();
      xo_img_Bind(NULL, 0);
      xo_render_EndDraw();
    }
    xo_render_EndDraw();
  }

  xo_render_EndDisplayList_Render();
  xo_render_DebugLog("stage 00");
  if(!s_Stage00.controllerPluggedIn)
  {
    xo_render_DebugLog("no controller");
  }
  xo_render_EndFrame();
}

void updateGame00(void)
{
  u8 i;
  f32 inputx, inputy;

  xo_controller_Update();
  // get the first plugged in controller
  i = xo_controller_GetIndex(0);

  if (xo_contoller_IsConnected(i))
  {
    s_Stage00.controllerPluggedIn = TRUE;

    xo_controller_GetAxisUnclamped(i, XO_AXIS_STICK, &inputx, &inputy);
    s_Stage00.x += inputx;
    s_Stage00.y += inputy;



    if (xo_controller_ButtonDown(i, XO_BUTTON_TRIGGER_Z)) {
      if (xo_controller_ButtonDown(i, XO_BUTTON_A)) {
        s_Stage00.theta += 3.0f;
      } else {
        s_Stage00.theta += 1.0f;
      }
    }

    //if (xo_controller_ButtonPressed(i, XO_BUTTON_START))
    //{
    //  nuGfxFuncRemove();
    //  stage = 1;
    //}
  }
  else
  {
    s_Stage00.controllerPluggedIn = FALSE;
  }
}

void BindMesh(Vtx* mesh, u16 vertCount)
{
  gSPVertex(g_Glist++, mesh, vertCount, 0);

  gDPPipeSync(g_Glist++);
  gDPSetCycleType(g_Glist++, G_CYC_1CYCLE);
  gDPSetRenderMode(g_Glist++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
  gSPClearGeometryMode(g_Glist++, 0xFFFFFFFF);
  gSPSetGeometryMode(g_Glist++, G_SHADE | G_SHADING_SMOOTH);
}

void ApplyMesh()
{

  gSP2Triangles(g_Glist++, 0, 1, 2, 0, 0, 2, 3, 0);
}
