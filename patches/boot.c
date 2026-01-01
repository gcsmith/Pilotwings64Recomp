#include "patches.h"

void _uvDebugPrintf(char* fmt, ...);
void func_8022E2DC(char arg0);

extern OSIoMesg D_802C32A8;
extern OSMesgQueue D_802C32C0;
extern s32 D_802B9C80;

extern char app_ROM_START[];
extern char app_ROM_END[];

RECOMP_PATCH void _uvDMA(void* vAddr, u32 devAddr, u32 nbytes) {
    s32 dest = (s32)vAddr;
    if (D_802B9C80 == 0) {
        if (dest % 8) {
            _uvDebugPrintf("_uvDMA: RAM address not 8 byte aligned 0x%x\n", dest);
            return;
        }
        if ((s32)devAddr % 2) {
            _uvDebugPrintf("_uvDMA: ROM address not 2 byte aligned 0x%x\n", devAddr);
            return;
        }
        if ((u32)osMemSize < nbytes) {
            _uvDebugPrintf("_uvDMA: nbytes invalid %d\n", (s32) nbytes);
            return;
        }
        if (nbytes & 1) {
            nbytes = (nbytes + 1) & ~1;
        }

        if (devAddr == (u32)app_ROM_START) {
            u32 size = (((u32) &app_ROM_END - (u32) &app_ROM_START) + 0xF) & ~0xF;
            recomp_load_overlays((u32)devAddr, (void*)dest, size);
        }

        osWritebackDCache((void* )dest, (s32)nbytes);
        osPiStartDma(&D_802C32A8, 0, 0, devAddr, (void*) dest, nbytes, &D_802C32C0);
        osInvalDCache((void*)dest, (s32)nbytes);
        func_8022E2DC(0);
    }
}

