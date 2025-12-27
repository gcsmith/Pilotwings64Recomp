#ifndef __PILOTWINGS64_SOUND_H__
#define __PILOTWINGS64_SOUND_H__

namespace pilotwings64 {
    void reset_sound_settings();
    void set_main_volume(int volume);
    int get_main_volume();
    void set_bgm_volume(int volume);
    int get_bgm_volume();
    void set_low_health_beeps_enabled(bool enabled);
    bool get_low_health_beeps_enabled();
}

#endif
