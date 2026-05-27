#include "pilotwings64_config.h"
#include "pilotwings64_debug.h"
#include "pilotwings64_sound.h"
#include "recompui/recompui.h"
#include "recompui/config.h"
#include "recompinput/recompinput.h"
#include "ultramodern/config.hpp"
#include "librecomp/files.hpp"
#include "librecomp/config.hpp"
#include "util/file.h"
#include <filesystem>
#include <fstream>
#include <iomanip>

#if defined(_WIN32)
#include <Shlobj.h>
#elif defined(__linux__)
#include <unistd.h>
#include <pwd.h>
#elif defined(__APPLE__)
#include "apple/rt64_apple.h"
#endif

static void add_general_options(recomp::config::Config &config) {
    using EnumOptionVector = const std::vector<recomp::config::ConfigOptionEnumOption>;

    static EnumOptionVector analog_cam_mode_options = {
        {pilotwings64::AnalogCamMode::Off, "Off", "Off"},
        {pilotwings64::AnalogCamMode::On, "On", "On"},
    };
    config.add_enum_option(
        pilotwings64::configkeys::general::analog_cam_mode,
        "Analog Camera",
        "Enables the analog camera.",
        analog_cam_mode_options,
        pilotwings64::AnalogCamMode::Off
    );
    config.add_number_option(
        pilotwings64::configkeys::general::analog_camera_sensitivity,
        "Analog Camera Sensitivity",
        "Sets the sensitivity of the right stick analog camera, if enabled.",
        1, 10, 1, 0, false, 3
    );
    config.add_option_hidden_dependency(
        pilotwings64::configkeys::general::analog_camera_sensitivity,
        pilotwings64::configkeys::general::analog_cam_mode,
        pilotwings64::AnalogCamMode::Off
    );
    static EnumOptionVector camera_invert_mode_options = {
        {pilotwings64::CameraInvertMode::InvertNone, "InvertNone", "None"},
        {pilotwings64::CameraInvertMode::InvertX, "InvertX", "Invert X"},
        {pilotwings64::CameraInvertMode::InvertY, "InvertY", "Invert Y"},
        {pilotwings64::CameraInvertMode::InvertBoth, "InvertBoth", "Invert Both"}
    };
    config.add_enum_option(
        pilotwings64::configkeys::general::third_person_camera_invert_mode,
        "Invert Camera",
        "Inverts the camera controls for the third person camera if it's enabled. <recomp-color primary>Invert X</recomp-color> is the default and matches the original game.<br /><br />If analog camera is off, only the <recomp-color primary>Invert X</recomp-color> setting will take effect.",
        camera_invert_mode_options,
        pilotwings64::CameraInvertMode::InvertX
    );
    static EnumOptionVector first_person_invert_mode_options = {
        {pilotwings64::CameraInvertMode::InvertNone, "InvertNone", "None"},
        {pilotwings64::CameraInvertMode::InvertX, "InvertX", "Invert X"},
        {pilotwings64::CameraInvertMode::InvertY, "InvertY", "Invert Y"},
        {pilotwings64::CameraInvertMode::InvertBoth, "InvertBoth", "Invert Both"}
    };
    config.add_enum_option(
        pilotwings64::configkeys::general::first_person_invert_mode,
        "Invert First Person View",
        "Inverts the camera controls in first person view. <recomp-color primary>Invert Y</recomp-color> is the default and matches the original game.",
        first_person_invert_mode_options,
        pilotwings64::CameraInvertMode::InvertY
    );
    static EnumOptionVector flying_and_swimming_invert_options = {
        {pilotwings64::CameraInvertMode::InvertNone, "InvertNone", "None"},
        {pilotwings64::CameraInvertMode::InvertX, "InvertX", "Invert X"},
        {pilotwings64::CameraInvertMode::InvertY, "InvertY", "Invert Y"},
        {pilotwings64::CameraInvertMode::InvertBoth, "InvertBoth", "Invert Both"}
    };
    config.add_enum_option(
        pilotwings64::configkeys::general::flying_and_swimming_invert_mode,
        "Invert Flying & Swimming",
        "Inverts the controls for swimming and flying. <recomp-color primary>Invert Y</recomp-color> is the default and matches the original game.",
        flying_and_swimming_invert_options,
        pilotwings64::CameraInvertMode::InvertY
    );
}

template <typename T = uint32_t>
T get_general_config_enum_value(const std::string& option_id) {
    return static_cast<T>(std::get<uint32_t>(recompui::config::get_general_config().get_option_value(option_id)));
}

template <typename T = uint32_t>
T get_general_config_number_value(const std::string& option_id) {
    return static_cast<T>(std::get<double>(recompui::config::get_general_config().get_option_value(option_id)));
}

pilotwings64::CameraInvertMode pilotwings64::get_camera_invert_mode() {
    return get_general_config_enum_value<pilotwings64::CameraInvertMode>(pilotwings64::configkeys::general::camera_invert_mode);
}

pilotwings64::CameraInvertMode pilotwings64::get_analog_camera_invert_mode() {
    return get_general_config_enum_value<pilotwings64::CameraInvertMode>(pilotwings64::configkeys::general::third_person_camera_invert_mode);
}

pilotwings64::AnalogCamMode pilotwings64::get_analog_cam_mode() {
    return get_general_config_enum_value<pilotwings64::AnalogCamMode>(pilotwings64::configkeys::general::analog_cam_mode);
}

uint32_t pilotwings64::get_analog_cam_sensitivity() {
    return get_general_config_number_value(pilotwings64::configkeys::general::analog_camera_sensitivity);
}

template <typename T = uint32_t>
T get_graphics_config_enum_value(const std::string& option_id) {
    return static_cast<T>(std::get<uint32_t>(recompui::config::get_graphics_config().get_option_value(option_id)));
}

static void add_sound_options(recomp::config::Config &config) {
    config.add_percent_number_option(
        pilotwings64::configkeys::sound::bgm_volume,
        "Background Music Volume",
        "Controls the overall volume of background music.",
        100.0f
    );
}

template <typename T = uint32_t>
T get_sound_config_number_value(const std::string& option_id) {
    return static_cast<T>(std::get<double>(recompui::config::get_sound_config().get_option_value(option_id)));
}

int pilotwings64::get_bgm_volume() {
    return get_sound_config_number_value<int>(pilotwings64::configkeys::sound::bgm_volume);
}

static void add_graphics_options(recomp::config::Config &config) {
    using EnumOptionVector = const std::vector<recomp::config::ConfigOptionEnumOption>;
    static EnumOptionVector cutscene_aspect_ratio_mode_options = {
        {pilotwings64::CutsceneAspectRatioMode::Original, "Original", "Original"},
        {pilotwings64::CutsceneAspectRatioMode::Clamp16x9, "Clamp16x9", "16:9"},
        {pilotwings64::CutsceneAspectRatioMode::Full, "Expand", "Expand"},
    };
    config.add_enum_option(
        pilotwings64::configkeys::graphics::cutscene_aspect_ratio_mode,
        "Cutscene Aspect Ratio",
        "Sets the aspect ratio limit for cutscenes. Cutscenes have been adjusted to work in <recomp-color primary>16:9</recomp-color>, which is the default option. Wider aspect ratios may show details that weren't meant to be on-screen.",
        cutscene_aspect_ratio_mode_options,
        pilotwings64::CutsceneAspectRatioMode::Clamp16x9
    );    
}

static void add_debug_options(recomp::config::Config &config) {
    config.add_bool_option(
        pilotwings64::configkeys::debug::trace_debug_printf,
        "Trace uvDebugPrintf",
        "Enables tracing of internal calls to uvDebugPrintf.",
        false
    );
    config.add_bool_option(
        pilotwings64::configkeys::debug::trace_emitter_printf,
        "Trace uvEmitterPrintf",
        "Enables tracing of internal calls to uvEmitterPrintf.",
        false
    );
    config.add_bool_option(
        pilotwings64::configkeys::debug::trace_recomp_funcs,
        "Trace RecompFuncs",
        "Enables tracing of internal recompiled function calls (trace_mode must be enabled).",
        false
    );
    config.add_bool_option(
        pilotwings64::configkeys::debug::override_max_lod,
        "Override Maximum LOD",
        "Overrides level-of-detal (LOD) selection to maximum detail.",
        true
    );
    config.add_bool_option(
        pilotwings64::configkeys::debug::override_proxanim_range,
        "Override ProxAnim Range",
        "Overrides proximity-based animation range to maximum detail.",
        true
    );
    config.add_bool_option(
        pilotwings64::configkeys::debug::remove_screen_border,
        "Remove Screen Border",
        "Remove black screen border present in the original game.",
        true
    );
}

template <typename T = uint32_t>
T get_debug_config_number_value(const std::string& option_id) {
    return static_cast<T>(std::get<double>(recompui::config::get_config("debug").get_option_value(option_id)));
}

inline bool get_debug_config_bool_value(const std::string& option_id) {
    return std::get<bool>(recompui::config::get_config("debug").get_option_value(option_id));
}

bool pilotwings64::get_trace_debug_printf() {
    return get_debug_config_bool_value(pilotwings64::configkeys::debug::trace_debug_printf);
}

bool pilotwings64::get_trace_emitter_printf() {
    return get_debug_config_bool_value(pilotwings64::configkeys::debug::trace_emitter_printf);
}

bool pilotwings64::get_trace_recomp_funcs() {
    return get_debug_config_bool_value(pilotwings64::configkeys::debug::trace_recomp_funcs);
}

bool pilotwings64::get_override_max_lod() {
    return get_debug_config_bool_value(pilotwings64::configkeys::debug::override_max_lod);
}

bool pilotwings64::get_override_proxanim_range() {
    return get_debug_config_bool_value(pilotwings64::configkeys::debug::override_proxanim_range);
}

bool pilotwings64::get_remove_screen_border() {
    return get_debug_config_bool_value(pilotwings64::configkeys::debug::remove_screen_border);
}

static void set_control_defaults() {
    using namespace recompinput;

    // Left shoulder -> C Down | Backwards eggs / zoom out
    set_default_mapping_for_controller(
        GameInput::C_DOWN,
        { 
            InputField::controller_analog(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY, true),
            InputField::controller_digital(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
        }
    );

    // Right shoulder -> C Up | Forwards eggs / first person
    set_default_mapping_for_controller(
        GameInput::C_UP,
        { 
            InputField::controller_analog(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY, false),
            InputField::controller_digital(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
        }
    );

    // North button -> C Left | Talon trot / camera left
    set_default_mapping_for_controller(
        GameInput::C_LEFT,
        { 
            InputField::controller_analog(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX, false),
            InputField::controller_digital(SDL_CONTROLLER_BUTTON_NORTH)
        }
    );

    // East button -> C Right | Wonderwing / camera right
    set_default_mapping_for_controller(
        GameInput::C_RIGHT,
        { 
            InputField::controller_analog(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX, true),
            InputField::controller_digital(SDL_CONTROLLER_BUTTON_EAST)
        }
    );

    // R3 -> L | Unused in BK but can be used in mods
    set_default_mapping_for_controller(GameInput::L, { InputField::controller_digital(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSTICK) });
}

static void set_control_descriptions() {
    recompinput::set_game_input_description(recompinput::GameInput::Y_AXIS_POS, "Used to move and for steering while flying and swimming. Axis inversion for flying and swimming can be configured in the General tab.");
    recompinput::set_game_input_description(recompinput::GameInput::Y_AXIS_NEG, "Used to move and for steering while flying and swimming. Axis inversion for flying and swimming can be configured in the General tab.");
    recompinput::set_game_input_description(recompinput::GameInput::X_AXIS_NEG, "Used to move and for steering while flying and swimming. Axis inversion for flying and swimming can be configured in the General tab.");
    recompinput::set_game_input_description(recompinput::GameInput::X_AXIS_POS, "Used to move and for steering while flying and swimming. Axis inversion for flying and swimming can be configured in the General tab.");
    recompinput::set_game_input_description(recompinput::GameInput::A, "Used to jump and select options in menus. Also used for flying upwards.");
    recompinput::set_game_input_description(recompinput::GameInput::B, "Used for attacks, which change depending on whether you are stationary, moving, in the air, or crouching.");
    recompinput::set_game_input_description(recompinput::GameInput::Z, "Used to crouch, which enables A, B and the C-Buttons to perform different actions.");
    recompinput::set_game_input_description(recompinput::GameInput::L, "Unused. Mods may use it for additional features.");
    recompinput::set_game_input_description(recompinput::GameInput::R, "Used to center the camera behind pilotwings64 on the ground, and to perform tighter turns while flying or swimming.");
    recompinput::set_game_input_description(recompinput::GameInput::START, "Used for pausing and for skipping certain cutscenes.");
    recompinput::set_game_input_description(recompinput::GameInput::C_UP, "Used to enter first-person mode, and to shoot eggs while holding Z.");
    recompinput::set_game_input_description(recompinput::GameInput::C_DOWN, "Used to toggle between the different camera zoom levels, and to shoot eggs backwards while holding Z.");
    recompinput::set_game_input_description(recompinput::GameInput::C_LEFT, "Used to rotate the camera sideways. Axis inversion can be configured in the General tab. Also used to enter Talon Trot while holding Z.");
    recompinput::set_game_input_description(recompinput::GameInput::C_RIGHT, "Used to rotate the camera sideways. Axis inversion can be configured in the General tab). Also used to enter Wonderwing while holding Z.");
    recompinput::set_game_input_description(recompinput::GameInput::DPAD_UP, "Unused. Mods may use it for additional features.");
    recompinput::set_game_input_description(recompinput::GameInput::DPAD_DOWN, "Unused. Mods may use it for additional features.");
    recompinput::set_game_input_description(recompinput::GameInput::DPAD_LEFT, "Unused. Mods may use it for additional features.");
    recompinput::set_game_input_description(recompinput::GameInput::DPAD_RIGHT, "Unused. Mods may use it for additional features.");
}

pilotwings64::CutsceneAspectRatioMode pilotwings64::get_cutscene_aspect_ratio_mode() {
    return get_graphics_config_enum_value<pilotwings64::CutsceneAspectRatioMode>(pilotwings64::configkeys::graphics::cutscene_aspect_ratio_mode);
}

void pilotwings64::init_config() {
    std::filesystem::path recomp_dir = recompui::file::get_app_folder_path();

    if (!recomp_dir.empty()) {
        std::filesystem::create_directories(recomp_dir);
    }

    recompui::config::GeneralTabOptions general_options{};
    general_options.has_rumble_strength = true;
    general_options.has_gyro_sensitivity = false;
    general_options.has_mouse_sensitivity = false;

    auto &general_config = recompui::config::create_general_tab(general_options);
    add_general_options(general_config);

    auto &graphics_config = recompui::config::create_graphics_tab();
    add_graphics_options(graphics_config);

    set_control_defaults();
    set_control_descriptions();
    recompui::config::create_controls_tab();

    auto &sound_config = recompui::config::create_sound_tab();
    add_sound_options(sound_config);

    recompui::config::create_mods_tab();

    auto &debug_config = recompui::config::create_config_tab("Debug", "debug", false);
    add_debug_options(debug_config);

    recompui::config::finalize();

}
