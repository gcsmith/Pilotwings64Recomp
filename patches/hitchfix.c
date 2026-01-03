#include "patches.h"

void _uvDebugPrintf(char* fmt, ...);
extern ALSeqPlayer* D_80248C90;
void func_80206150(s32 arg0);
f64 uvClkGetSec(s32 clk_id);

void yield_self_1ms(void);

RECOMP_PATCH void uvaSeqStop(void) {
    alSeqpStop(D_80248C90);
    func_80206150(7);
    if (alSeqpGetState(D_80248C90) != 0) {
        do {
            yield_self_1ms();
            if (uvClkGetSec(7) > 2.0) {
                _uvDebugPrintf("uvaSeqStop timed out\n");
                return;
            }
        }
        while (alSeqpGetState(D_80248C90) != 0);
    }
}

