#include "patches.h"
#include "uv_graphics.h"
#include "uv_math.h"
#include "app/game.h"
#include "app/proxanim.h"

extern ProxAnim sProxAnimSlots[40];

RECOMP_PATCH f32 proxAnimGetRange(s32 proxId) {
    Unk80362690_Unk0* temp_v1;
    ProxAnim* prox;
    f32 dx, dy, dz;

    temp_v1 = &D_80362690->unkC[D_80362690->unk9C];
    prox = &sProxAnimSlots[proxId];

    if ((proxId < 0) || (proxId >= ARRAY_COUNT(sProxAnimSlots)) || (prox->dist == 0.0f)) {
        _uvDebugPrintf("Proxanim: Bad id %d passed to panm_getrange\n", proxId);
        return 0.0f;
    }

    dx = temp_v1->unk2C.m[3][0] - prox->pos.x;
    dy = temp_v1->unk2C.m[3][1] - prox->pos.y;
    dz = temp_v1->unk2C.m[3][2] - prox->pos.z;
#ifndef ENABLE_ENHANCEMENTS
    return uvLength3D(dx, dy, dz);
#else
    return 1.0f;
#endif
}

void lod_dummy(void) {
    return;
}

