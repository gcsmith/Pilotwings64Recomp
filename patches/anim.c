#include "patches.h"
#include "uv_graphics.h"

RECOMP_PATCH u8 uvDobjGetLODIndex(ParsedUVMD* uvmd, f32 dist) {
    u8 lodCount;
    u8 i;
    f32* lodRadius;

    lodRadius = uvmd->lodRadius;
    lodCount = uvmd->lodCount;
    if (lodRadius[lodCount - 1] <= dist) {
        return 0xFF;
    }

#ifndef ENABLE_ENHANCEMENTS
    for (i = lodCount; i > 0; i--) {
        if (lodRadius[i - 1] < dist) {
            return i;
        }
    }
#endif
    return 0;
}

RECOMP_PATCH u8 uvSobjGetLODIndex(ParsedUVMD* uvmd, f32 dist) {
    s32 lodCount;
    s32 i;
    f32* lodRadius;

    lodRadius = uvmd->lodRadius;
    lodCount = uvmd->lodCount;
    if (lodRadius[lodCount - 1] <= dist) {
        return 0xFF;
    }

#ifndef ENABLE_ENHANCEMENTS
    for (i = lodCount; i > 0; i--) {
        if (lodRadius[i - 1] < dist) {
            return i;
        }
    }
#endif
    return 0;
}

void anim_dummy(void) {
    return;
}

