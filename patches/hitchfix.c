#include "patches.h"

void _uvDebugPrintf(char* fmt, ...);
extern ALSeqPlayer* gSeqPlayer;
void uvClkReset(s32 arg0);
f64 uvClkGetSec(s32 clk_id);

void yield_self_1ms(void);

RECOMP_PATCH void uvaSeqStop(void) {
    alSeqpStop(gSeqPlayer);
    uvClkReset(7);
    if (alSeqpGetState(gSeqPlayer) != 0) {
        do {
            yield_self_1ms();
            if (uvClkGetSec(7) > 2.0) {
                _uvDebugPrintf("uvaSeqStop timed out\n");
                return;
            }
        }
        while (alSeqpGetState(gSeqPlayer) != 0);
    }
}

