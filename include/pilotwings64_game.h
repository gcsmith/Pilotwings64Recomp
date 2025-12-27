#ifndef __PILOTWINGS64_GAME_H__
#define __PILOTWINGS64_GAME_H__

#include <cstdint>
#include <span>
#include <vector>

namespace pilotwings64 {
    void quicksave_save();
    void quicksave_load();
    std::vector<uint8_t> decompress_mm(std::span<const uint8_t> compressed_rom);
};

#endif
