#include <atomic>
#include <iostream>
#include "spdlog/spdlog.h"
#include "pilotwings64_debug.h"
#include "librecomp/helpers.hpp"
#include "ultramodern/ultramodern.hpp"
#include "../patches/input.h"

namespace pilotwings64 { std::string get_game_thread_name(const OSThread* t); }

inline auto current_game_thread(uint8_t *rdram) -> std::string
{
    if (!ultramodern::is_entrypoint_thread()) {
        return pilotwings64::get_game_thread_name(TO_PTR(OSThread, ultramodern::this_thread())).substr(7);
    } else {
        return "ENTRY";
    }
}

extern "C" void pilotwings64_trace_init()
{
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [tid %t] [%^%l%$] : %v");
}

extern "C" void pilotwings64_trace_debug(uint8_t *rdram, const char *mesg)
{
    spdlog::info("[{}] uvDebugPrintf: {}", current_game_thread(rdram), mesg);
}

extern "C" void pilotwings64_trace_entry(uint8_t *rdram, const char *func)
{
    if (pilotwings64::get_trace_recomp_funcs()) {
        spdlog::info("[{}] trace_entry: {}", current_game_thread(rdram), func);
    }
}

extern "C" void pilotwings64_trace_return(uint8_t *rdram, const char *func)
{
    if (pilotwings64::get_trace_recomp_funcs()) {
        spdlog::info("[{}] trace_return: {}", current_game_thread(rdram), func);
    }
}

