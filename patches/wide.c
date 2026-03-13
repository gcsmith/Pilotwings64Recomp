#include "patches.h"
#include "uv_geometry.h"
#include "uv_graphics.h"

RECOMP_PATCH void func_8034B688(void) {
    uvGfx_80223A28(0xFFF);
#ifndef ENABLE_ENHANCEMENTS
    uvVtxRect(0, 0x12, 0x13F, 0);
    uvVtxRect(0, 0xEF, 0x13F, 0xE8);
    uvVtxRect(0, 0xE8, 0xA, 0x12);
    uvVtxRect(0x136, 0xE8, 0x13F, 0x12);
#endif
}

void wide_dummy(void) {
    return;
}

