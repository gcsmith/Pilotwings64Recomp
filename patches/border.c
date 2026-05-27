#include "debug.h"
#include "patches.h"
#include "uv_geometry.h"
#include "uv_graphics.h"
#include "app/code_66160.h"
#include "app/code_72010.h"
#include "app/camera.h"
#include "app/hud.h"
#include "app/task.h"

extern Unk803599D0 D_803599D0;
extern uvGfxViewport_t gGfxViewports[4];
extern s16 gGfxViewX0;
extern s16 gGfxViewX1;
extern s16 gGfxViewY0;
extern s16 gGfxViewY1;

extern void cameraSetViewport(Camera* camera, s16 x0, s16 x1, s16 y0, s16 y1);

extern void func_80314154(void);
extern void func_803141E4(void);

extern f32 D_8036A8C0;
extern f32 D_8036A8C4;
extern u8 D_8036A8D4[CLASS_COUNT];
extern u8 D_8036A8D8[CLASS_COUNT];
extern u8 D_8034F7B0;
extern u8 D_8034F7B8;

RECOMP_PATCH void drawScreenBorder(void) {
    if (!recomp_get_remove_screen_border()) {
        uvGfxBindTexture(GFX_STATE_TEXTURE_NONE);
        uvVtxRect(0, SUBSCREEN_Y0, SCREEN_WIDTH - 1, 0);
        uvVtxRect(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SUBSCREEN_Y1);
        uvVtxRect(0, SUBSCREEN_Y1, SUBSCREEN_X0, SUBSCREEN_Y0);
        uvVtxRect(SUBSCREEN_X1, SUBSCREEN_Y1, SCREEN_WIDTH - 1, SUBSCREEN_Y0);
    }
}

RECOMP_PATCH void func_8030F448(void) {
    s32 i;

    func_80314154();
    uvGfxSetFlags(GFX_STATE_AA);

    if (!recomp_get_remove_screen_border()) { // FIXME: expand with extended gbi
        uvVtxBeginPoly();
        uvVtx(0, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, 100);
        uvVtx(0, 0, 0, 0, 0, 0, 0, 0, 100);
        uvVtx(SCREEN_WIDTH, 0, 0, 0, 0, 0, 0, 0, 100);
        uvVtx(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, 100);
        uvVtxEndPoly();
    }

    uvGfxClearFlags(GFX_STATE_AA);
    func_803141E4();
    if (D_8034F7B0 == 0) {
        uvSprtDraw(17);
        uvSprtDraw(18);
        if ((D_8036A8D4[0] != 0) || (D_8036A8D4[1] != 0) || (D_8036A8D4[2] != 0) || (D_8036A8D4[3] != 0)) {
            uvSprtDraw(21);
        }
    } else {
        uvSprtDraw(19);
        uvSprtDraw(20);
    }
    if (D_8034F7B0 == 0) {
        for (i = 0; i < 12; i++) {
            uvSprtDraw(i);
        }

        for (i = 1; i < 4; i++) {
            if (D_8036A8D8[i] == FALSE) {
                uvSprtDraw(i + 11);
            }
        }
    } else {
        for (i = 0; i < 9; i++) {
            uvSprtDraw(i);
        }
        for (i = 0; i < 4; i++) {
            if (D_8036A8D4[i] == FALSE) {
                uvSprtDraw(i + 9);
            }
        }
        for (i = 1; i < 4; i++) {
            if (D_8036A8D8[i] == FALSE) {
                uvSprtDraw(i + 12);
            }
        }
    }

    func_80314154();
    if (D_8034F7B8 == 0) {
        func_802DEE44(D_8036A8C0 + 0.5, D_8036A8C4 + 0.5, 0x34, 0x26, 3, 0xFA, 0xFA, 0, 0xFA, 0xFA, 0);
    } else {
        func_802DEE44(D_8036A8C0 + 0.5, D_8036A8C4 + 0.5, 0x29, 0x20, 3, 0xFA, 0xFA, 0, 0xFA, 0xFA, 0);
    }

    if (!recomp_get_remove_screen_border()) {
        uvGfxBindTexture(GFX_STATE_TEXTURE_NONE);
        uvVtxRect(0, SUBSCREEN_Y0, SCREEN_WIDTH - 1, 0);
        uvVtxRect(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SUBSCREEN_Y1);
        uvVtxRect(0, SUBSCREEN_Y1, SUBSCREEN_X0, SUBSCREEN_Y0);
        uvVtxRect(SUBSCREEN_X1, SUBSCREEN_Y1, SCREEN_WIDTH - 1, SUBSCREEN_Y0);
    }
    func_803141E4();
}

RECOMP_PATCH void cameraInit(u8 unkIndex, Camera* camera) {
    f32 one;
    one = 1.0f;
    uvChan_80204A8C(unkIndex, 3);
    func_802EAAE0(&camera->unk230);
    camera->unk2 = camera->unk1;
    camera->unk0 = 0;

    if (recomp_get_remove_screen_border()) {
        camera->viewX0 = 0;
        camera->viewX1 = SCREEN_WIDTH;
        camera->viewY0 = 0;
        camera->viewY1 = SCREEN_HEIGHT;
    }
    else {
        camera->viewX0 = SUBSCREEN_X0;
        camera->viewX1 = SUBSCREEN_X1;
        camera->viewY0 = SUBSCREEN_Y0;
        camera->viewY1 = SUBSCREEN_Y1;
    }
    camera->clipNear = 1.0f;
    camera->clipFar = 2000.0f;
    camera->clipX0 = one * -0.4906542f;
    camera->clipX1 = one * 0.4906542f;
    camera->clipY0 = one * -0.35f;
    camera->clipY1 = one * 0.35f;
    camera->unk48 = 0.7f;
    camera->unk4C = 0.6f;
    camera->unk5C = 0.0f;
    camera->unk60 = -4.0f;
    camera->unk64 = -1.0f;
    camera->unk54 = 1.8f;
    camera->unk58 = 10.0f;
    camera->unk50 = 0.0f;
    camera->unk68.x = 0;
    camera->unkD = 1;
    camera->unk68.y = -1.2f;
    camera->unk68.z = -0.2f;
    camera->unk74 = -0.1f;
    camera->unk190 = 6.0f;
    camera->unk194 = 0.0f;
    camera->unk19C = 0.5f;
    camera->unk198 = 0.52359873f; // almost DEG_TO_RAD(30)
    camera->unkE = 1;
    camera->unkC = 1;
    camera->unk1A8 = 0.0f;
    camera->unk1AC = 0.0f;
    camera->unk1B0 = 0.0f;
    camera->unk200 = 0.0f;
    camera->unk204.x = 0.0f;
    camera->unk204.y = 0.0f;
    camera->unk204.z = 0.0f;
    camera->unk21C = 0.0f;
    camera->unk220 = 0.0f;
    camera->unk20 = 0.0f;
    camera->unk14 = 0.0f;
    camera->unk1C = 1;
    camera->unk78 = 0.0f;
    camera->unk7C = 0.0f;
    camera->unk1B4 = 6.0f;
    camera->unk1B8 = 6.0f;
    camera->unk22C = unkIndex;
    camera->unk1A4 = 0.0f;
    camera->unk224 = 1;
    camera->unk1114 = 1;
    camera->unk4 = 0xFFFF;
    camera->unk6 = 0;
    camera->unk148 = 0;
    camera->unkF = 0;
    camera->unk8 = 16.0f;
    camera->unk1A0 = 0.1f;
    camera->unk137C = 0;
    camera->unk108.m[3][2] = 0.0f;
    camera->unk1380 = 0.0f;
    camera->unk1374 = 6.0f;
    camera->unk1378 = 30.0f;
    uvMat4SetIdentity(&camera->unk80);
    cameraSetViewport(camera, camera->viewX0, camera->viewX1, camera->viewY0, camera->viewY1);
    camera_802D45C4(camera, 1);
    D_803599D0.count = 6;
    D_803599D0.unk4[0].x = 0.0f;
    D_803599D0.unk4[0].y = 0.0f;
    D_803599D0.unk4[1].x = 5.0f;
    D_803599D0.unk4[1].y = 5.0f;
    D_803599D0.unk4[2].x = 10.0f;
    D_803599D0.unk4[2].y = 9.0f;
    D_803599D0.unk4[3].x = 15.0f;
    D_803599D0.unk4[3].y = 12.0f;
    D_803599D0.unk4[4].x = 20.0f;
    D_803599D0.unk4[4].y = 13.5f;
    D_803599D0.unk4[5].x = 25.0f;
    D_803599D0.unk4[5].y = 14.5f;
}

RECOMP_PATCH void uvGfxClipRect(uvGfxViewport_t* vp, s32 x0, s32 x1, s32 y0, s32 y1) {
    s32 var_a2;
    s32 var_a3;

    vp->x0 = x0;
    vp->x1 = x1;
    vp->y0 = y0;
    vp->y1 = y1;
    if (vp->x0 < 0) {
        vp->x0 = 0;
    } else if (vp->x0 > SCREEN_WIDTH) {
        vp->x0 = SCREEN_WIDTH;
    }

    if (vp->x1 < 0) {
        vp->x1 = 0;
    } else if (vp->x1 > SCREEN_WIDTH) {
        vp->x1 = SCREEN_WIDTH;
    }

    if (vp->y1 < 0) {
        vp->y1 = 0;
    } else if (vp->y1 > SCREEN_HEIGHT) {
        vp->y1 = SCREEN_HEIGHT;
    }

    if (vp->y0 < 0) {
        vp->y0 = 0;
    } else if (vp->y0 > SCREEN_HEIGHT) {
        vp->y0 = SCREEN_HEIGHT;
    }

    vp->unk0 = vp->x0 - 5;
    if (vp->unk0 < 0) {
        vp->unk0 = 0;
    }
    vp->unk2 = vp->x1 + 5;
    if (vp->unk2 > SCREEN_WIDTH) {
        vp->unk2 = SCREEN_WIDTH;
    }
    vp->unk4 = vp->y0 - 5;
    if (vp->unk4 < 0) {
        vp->unk4 = 0;
    }
    vp->unk6 = vp->y1 + 5;
    if (vp->unk6 > SCREEN_HEIGHT) {
        vp->unk6 = SCREEN_HEIGHT;
    }

    var_a2 = vp->unk2 - vp->unk0;
    var_a3 = vp->unk6 - vp->unk4;

    vp->vp.vp.vscale[0] = (var_a2 << 1);
    vp->vp.vp.vscale[1] = (var_a3 << 1);
    vp->vp.vp.vscale[2] = 0x1FF;
    vp->vp.vp.vscale[3] = 0;
    vp->vp.vp.vtrans[0] = (u16)((vp->unk0 + (var_a2 >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[1] = (u16)(((SCREEN_HEIGHT - vp->unk4) - (var_a3 >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[2] = 0x1FF;
    vp->vp.vp.vtrans[3] = 0;
    gGfxViewX0 = vp->x0;
    gGfxViewX1 = vp->x1;
    gGfxViewY0 = vp->y0;
    gGfxViewY1 = vp->y1;
}

