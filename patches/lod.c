#include "patches.h"
#include "uv_graphics.h"
#include "uv_math.h"
#include "app/code_72B70.h"

typedef struct { // XXX move to header
    u8 pad0[0xC];
    f32 unkC;
    u8 pad10[8];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} Unk8036D340; // size = 0x24

extern Unk8036D340 D_8036D340[];

RECOMP_PATCH f32 func_80321420(s32 arg0) {
    Unk80362690_Unk0_UnkC* temp_v1;
    Unk8036D340* temp_v0;
    f32 dx, dy, dz;

    temp_v1 = &D_80362690->unk0[D_80362690->unk9C].unkC;
    temp_v0 = &D_8036D340[arg0];
 
    if ((arg0 < 0) || (arg0 >= 0x28) || (temp_v0->unkC == 0.0f)) {
        _uvDebugPrintf("Proxanim: Bad id %d passed to panm_getrange\n\0Proxanim: Activating animation %d\n\0Proxanim: Init for anim %d requested deactivation\n\0Proxanim: Calling anim proc for %d, time %f\n\0Proxanim: Anim %d is done.\n\0Proxanim: Anim %d is deactivating.\n", arg0);
        return 0.0f;
    }
    
    dx = temp_v1->unk2C.m[3][0] - temp_v0->unk18;
    dy = temp_v1->unk2C.m[3][1] - temp_v0->unk1C;
    dz = temp_v1->unk2C.m[3][2] - temp_v0->unk20;
#ifndef ENABLE_ENHANCEMENTS
    return uvLength3D(dx, dy, dz);
#else
    return 1.0f;
#endif
}

void lod_dummy(void) {
    return;
}

