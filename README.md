# Pilotwings 64: Recompiled
[Pilotwings 64: Recompiled](https://github.com/gcsmith/Pilotwings64Recomp) is a project that uses [N64: Recompiled](https://github.com/Mr-Wiseguy/N64Recomp) to **statically recompile** Pilotwings 64 into a native port with many new features, enhancements, and extensive mod support. This project uses [RT64](https://github.com/rt64/rt64) as the rendering engine to provide graphical enhancements.

### ~~[Check out the latest release here](https://github.com/gcsmith/Pilotwings64Recomp/releases/latest)~~ (coming soon).

> [!IMPORTANT]
> This recomp is in early development. While it is currently playable, it is unpolished and lacks some basic features (e.g., border removal, widescreen support). Until then, this project must be built from the sources and is only made public for those that are either curious or interested in contributing.

Join the [N64: Recompiled Community Discord](https://discord.gg/AWZThJ4dPf) to discuss this and other N64: Recompiled projects!

[![Discord Invitation](https://discordapp.com/api/guilds/1374083583739826328/widget.png?style=banner2 'N64 Recomp')](https://discord.gg/AWZThJ4dPf)

### **This repository and its releases do not contain game assets. The original game is required to build or run this project.**

## Table of Contents
* [System Requirements](#system-requirements)
* [Known Issues](#known-issues)
* [Building](#building)
* [Dependencies](#dependencies)

## System Requirements
A GPU supporting Direct3D 12.0 (Shader Model 6), Vulkan 1.2, or Metal Argument Buffers Tier 2 support is required to run this project. The oldest GPUs that should be supported for each vendor are:
* GeForce GT 630
* Radeon HD 7750 (the one from 2012, not to be confused with the RX 7000 series) and newer
* Intel HD 510 (Skylake)
* A Mac with Apple Silicon or an Intel 7th Gen CPU with MacOS 13.0+

On x86-64 PCs, a CPU supporting the SSE4.1 instruction set is also required (Intel Core 2 Penryn series or AMD Bulldozer and newer). ARM64 builds will work on any ARM64 CPU.

If you have issues with crashes on startup, make sure your graphics drivers are fully up to date. 

## Known Issues
* Overlays such as MSI Afterburner and other software such as Wallpaper Engine can cause performance issues with this project that prevent the game from rendering correctly. Disabling such software is recommended.

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
