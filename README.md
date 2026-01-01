# Pilotwings 64: Recompiled
[Pilotwings 64: Recompiled](https://github.com/gcsmith/Pilotwings64Recomp) is a project that uses [N64: Recompiled](https://github.com/Mr-Wiseguy/N64Recomp) to **statically recompile** Pilotwings 64 into a native port with many new features, enhancements, and extensive mod support. This project uses [RT64](https://github.com/rt64/rt64) as the rendering engine to provide graphical enhancements.

This project is very early in development. The game is playable in its current state, but with some issues outlined below.

Currently only tested on Apple M4 silicon, but Windows and Linux should also work and will be tested / supported soon.

### ~~[Check out the latest release here](https://github.com/gcsmith/Pilotwings64Recomp/releases/latest)~~ (coming soon).

Join the [N64: Recompiled Community Discord](https://discord.gg/AWZThJ4dPf) to discuss this and other N64: Recompiled projects!

[![Discord Invitation](https://discordapp.com/api/guilds/1374083583739826328/widget.png?style=banner2 'N64 Recomp')](https://discord.gg/AWZThJ4dPf)

## Table of Contents
* [Known Issues](#known-issues)
* [Building](#building)
* [Dependencies](#dependencies)

## Known Issues
* Sound effects are currently missing.
* Significant hitching between scene transitions (e.g. landing / crashing).

## Building
Prebuilt binaries are not currently available, and likely won't be until a future 1.0 release.

Instructions on how to build this project can be found in the [BUILDING.md](BUILDING.md) file.

## Dependencies
* [N64Recomp](https://github.com/Mr-Wiseguy/N64Recomp) for static recompilation
* [RT64](https://github.com/rt64/rt64) for the project's rendering engine
* [RmlUi](https://github.com/mikke89/RmlUi) for building the menus and launcher
* [lunasvg](https://github.com/sammycage/lunasvg) for SVG rendering, used by RmlUi
* [FreeType](https://freetype.org/) for font rendering, used by RmlUi  
* [moodycamel::ConcurrentQueue](https://github.com/cameron314/concurrentqueue) for semaphores and fast, lock-free MPMC queues
* [Gamepad Motion Helpers](https://github.com/JibbSmart/GamepadMotionHelpers) for sensor fusion and calibration algorithms to implement gyro aiming
* [Pilotwings64Decomp](https://github.com/gcsmith/Pilotwings64Decomp) for symbols, headers and function definitions used for making patches and enhancements
* [ares](https://github.com/ares-emulator/ares) for RSP vector instruction reference implementations, used in RSP recompilation
