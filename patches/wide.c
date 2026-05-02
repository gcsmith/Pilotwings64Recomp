#include "patches.h"
#include "uv_geometry.h"
#include "uv_graphics.h"

RECOMP_PATCH void func_8034B688(void) {
    uvGfxBindTexture(GFX_STATE_TEXTURE_NONE);
#ifndef ENABLE_ENHANCEMENTS
    uvVtxRect(0, 18, 319, 0);
    uvVtxRect(0, 239, 319, 232);
    uvVtxRect(0, 232, 10, 18);
    uvVtxRect(310, 232, 319, 18);
#endif
}

void wide_dummy(void) {
    return;
}

