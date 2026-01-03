#include "patches.h"

extern ALSeqPlayer* D_80248C90;
void func_80206150(s32 arg0);
f64 uvClkGetSec(s32 clk_id);

RECOMP_PATCH void uvaSeqStop(void) {
    alSeqpStop(D_80248C90);
    func_80206150(7);
    if (alSeqpGetState(D_80248C90) != 0) {
        do {
            if (uvClkGetSec(7) > 0.001) { // reduced from 2 seconds -- thread isn't yielding??
                _uvDebugPrintf("uvaSeqStop timed out\n");
                return;
            }
        }
        while (alSeqpGetState(D_80248C90) != 0);
    }
}

