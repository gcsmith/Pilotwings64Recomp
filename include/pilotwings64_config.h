#ifndef __PILOTWINGS64_CONFIG_H__
#define __PILOTWINGS64_CONFIG_H__

#include <filesystem>
#include <string>
#include <string_view>

namespace pilotwings64 {
    inline const std::u8string program_id = u8"Pilotwings64Recompiled";
    inline const std::string program_name = "Pilotwings 64: Recompiled";

    namespace configkeys {
        namespace general {
            inline const std::string camera_invert_mode = "camera_invert_mode";
            inline const std::string analog_cam_mode = "analog_cam_mode";
            inline const std::string third_person_camera_invert_mode = "third_person_camera_invert_mode";
            inline const std::string flying_and_swimming_invert_mode = "flying_and_swimming_invert_mode";
            inline const std::string first_person_invert_mode = "first_person_invert_mode";
            inline const std::string analog_camera_sensitivity = "analog_camera_sensitivity";
        }

        namespace sound {
            inline const std::string bgm_volume = "bgm_volume";
        }

        namespace graphics {
            inline const std::string cutscene_aspect_ratio_mode = "cutscene_aspect_ratio_mode";
        }

        namespace debug {
            inline const std::string trace_debug_printf = "trace_debug_printf";
            inline const std::string trace_emitter_printf = "trace_emitter_printf";
            inline const std::string trace_recomp_funcs = "trace_recomp_funcs";
            inline const std::string override_max_lod = "override_max_lod";
            inline const std::string override_proxanim_range = "override_proxanim_range";
            inline const std::string remove_screen_border = "remove_screen_border";
        }
    }

    // TODO: Move loading configs to the runtime once we have a way to allow per-project customization.
    void init_config();

    enum class CameraInvertMode {
        InvertNone,
        InvertX,
        InvertY,
        InvertBoth
    };

    CameraInvertMode get_camera_invert_mode();

    CameraInvertMode get_analog_camera_invert_mode();

    enum class AnalogCamMode {
        On,
        Off,
        OptionCount
    };

    AnalogCamMode get_analog_cam_mode();

    uint32_t get_analog_cam_sensitivity();

    enum class CutsceneAspectRatioMode {
        Original,
        Clamp16x9,
        Full,
        OptionCount
    };

    CutsceneAspectRatioMode get_cutscene_aspect_ratio_mode();

    void open_quit_game_prompt();
};

#endif
