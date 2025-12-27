#include "patches.h"

#if 0
#include "misc_funcs.h"
#include "libc/stdarg.h"

typedef unsigned int size_t;

typedef char *outfun(char*,const char*,size_t);

int _Printf(outfun prout, char *arg, const char *fmt, __builtin_va_list args);

char* proutPrintf(char* dst, const char* fmt, size_t size) {
    recomp_puts(fmt, size);
    return (void*)1;
}

int recomp_printf(const char* fmt, ...) {
    __builtin_va_list args;
    __builtin_va_start(args, fmt);

    int ret = _Printf(&proutPrintf, NULL, fmt, args);

    __builtin_va_end(args);

    return ret;
}
#endif

void dummyfunc(void) {
    return;
}

