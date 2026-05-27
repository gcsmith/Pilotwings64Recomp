#ifndef __PILOTWINGS64_DEBUG_H__
#define __PILOTWINGS64_DEBUG_H__

namespace pilotwings64 {
    bool get_trace_debug_printf();
    bool get_trace_emitter_printf();
    bool get_trace_recomp_funcs();
    bool get_override_max_lod();
    bool get_override_proxanim_range();
    bool get_remove_screen_border();
}

extern "C" void pilotwings64_trace_init();
extern "C" void pilotwings64_trace_debug(uint8_t *rdram, const char *mesg);
extern "C" void pilotwings64_trace_entry(uint8_t *rdram, const char *func);
extern "C" void pilotwings64_trace_return(uint8_t *rdram, const char *func);

#endif

