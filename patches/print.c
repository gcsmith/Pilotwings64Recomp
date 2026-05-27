#include "debug.h"
#include "patches.h"
#include "uv_string.h"

#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_arg   __builtin_va_arg
#define va_end   __builtin_va_end

s32 uvSprintf_n(char* dest, const char* fmt, va_list ap) {
    s32 srcBufPos;
    s32 j;
    s32 destBufPos;
    char padStrBuf[0x5C];
    char* argStr;
    s32 arg;
    s32 padCount;
    int hasZeroPadding;
    int leftJustify;
    u8 c;
    int parseSpecifier;

    c = fmt[0];
    parseSpecifier = FALSE;
    srcBufPos = 0;
    destBufPos = 0;
    while (c != 0) {
        if (!parseSpecifier) {
            if (c == '%') {
                padCount = -1;
                leftJustify = FALSE;
                hasZeroPadding = FALSE;
                parseSpecifier = TRUE;
            } else {
                dest[destBufPos] = c;
                destBufPos++;
            }
        } else {
            if (c == '-') {
                srcBufPos++;
                c = fmt[srcBufPos];
                leftJustify = TRUE;
            }
            if (c == '\0') {
                break;
            }
            if (c == '0') {
                srcBufPos++;
                c = fmt[srcBufPos];
                hasZeroPadding = TRUE;
            }
            if (c == '\0') {
                break;
            }
            if ((c >= '1') && (c <= '9')) {
                j = 0;
                while ((c >= '0') && (c <= '9')) {
                    padStrBuf[j] = c;
                    srcBufPos++;
                    j++;
                    c = fmt[srcBufPos];
                }
                padStrBuf[j] = '\0';
                padCount = uvAtoi(padStrBuf);
            }
            if (c == '\0') {
                break;
            }
            if (c == '.') {
                srcBufPos++;
                j = 0;
                c = fmt[srcBufPos];
                while ((c >= '0') && (c <= '9')) {
                    padStrBuf[j] = c;
                    srcBufPos++;
                    j++;
                    c = fmt[srcBufPos];
                }
                padStrBuf[j] = '\0';
            }
            if (c == '\0') {
                break;
            }
            if (c == 'x') {
                arg = va_arg(ap, s32);
                strFormatInt(arg, 16, &destBufPos, dest, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (c == 'd') {
                arg = va_arg(ap, s32);
                strFormatInt(arg, 10, &destBufPos, dest, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (c == 'b') {
                arg = va_arg(ap, s32);
                strFormatInt(arg, 2, &destBufPos, dest, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (c == 'f') {
                strFormatFloat(va_arg(ap, f64), &destBufPos, dest);
                parseSpecifier = FALSE;
            } else if (c == 's') {
                argStr = va_arg(ap, char*);
                parseSpecifier = FALSE;
                while (*argStr != 0) {
                    dest[destBufPos] = *argStr++;
                    destBufPos++;
                }
            }
        }
        srcBufPos++;
        c = fmt[srcBufPos];
    }
    dest[destBufPos] = 0;
    return destBufPos;
}

RECOMP_PATCH void _uvDebugPrintf(char* fmt, ...) {
    static char sBuffer[1024];
    va_list args;

    if (recomp_get_trace_debug_printf()) {
        va_start(args, fmt);
        s32 length = uvSprintf_n(sBuffer, fmt, args);
        recomp_puts(sBuffer, length);
        va_end(args);
    }
}

RECOMP_PATCH void uvEmitterPrintf(const char* fmt, ...) {
    static char sBuffer[1024];
    va_list args;

    if (recomp_get_trace_emitter_printf()) {
        va_start(args, fmt);
        s32 length = uvSprintf_n(sBuffer, fmt, args);
        recomp_puts(sBuffer, length);
        va_end(args);
    }
}

void dummyfunc(void) {
    return;
}

