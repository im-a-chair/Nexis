<!-- [![Build Status](https://img.shields.io/github/actions/workflow/status/im-a-chair/Nexis/main.yml?branch=main)](https://github.com/im-a-chair/Nexis/actions?query=workflow%3Amain)-->
[![License](https://img.shields.io/badge/license-MIT-orange.svg)](./LICENSE.md)
[![Version](https://img.shields.io/badge/version-v0.6-brightgreen.svg)]()

# Nexis Game Engine

<!-- logo & title banner -->
<!-- <br> -->

The Nexis Game Engine is a Game Engine that aims to allow use through both pure code and a GUI/IDE, and the ability to switch between them anytime. And it aims to be as dynamic as possible while still maintaining a highly consurrent and optimized data oriented architecture.

### Design & Goal/Aim

The Nexis Game Engine came forth out of a frustration with game engines like Unity and Godot. Where for nearly everything, both the GUI/IDE and scripting are required. I myself as a programmer really prefer plain text based workflow, but other team members like artists, directors and designers tend to prefer the GUI based workflow. Thus I decided "I'll just make my own game engine". With the goal of making an engine that offers the option to both, work in text and work in the GUI, and most of all switch whenever you feel like it.

Thus the aim is to be dynamic in mainly two ways/places:
- **The IDE:** The main goal and initial reason i started the engine was to make a game engine that though it offers a IDE/Scene-Editor, it doesnt require it for any thing at any point. I think that a Game Engine's Scene-Editor and visual GUI tools should be a tool, and nothing more. I myself, as a programmer, prefer to work in just code, though when making games not just programmers are involved, also peopl that do visual art work, and other non-technical work which means they require a easy way to do just their job, thus most game engines now have chosen a GUI over plain code (with plenty code bases being a engine of just code). But I think its best to have **both**, and have the choice to switch any time, whenever you want.
- **The Framework:** The other, arguably more significant way in which the engine aims to be dynamic is the framework. The engine is (for several reasons) mainly just a core architecture, with only the `Core` module of the framework being required for nearly everything to work. In this, the engine aims to allow you to dynamically add, remove or swap sub-engines/modules and use different ones for different scenes. This is also part of the approach to making the engine usable in just code.

## Architecture

Because of the goal for a highly dynamic engine, the project itself is mainly the `Core` (being the actual engine) with a 'default' usable version of each basic component like physics, rendering, input, scripting, etc... (planned).

### Core lib

The core of the library is made up of a few systems that together form the main architecture and API:
- **Job system**, this is the most fundemental component, giving the architecture it's base concurrency. It has a built in fibers system, each JobPool you make has its own thread pool, where each thread has its own Job queue, Fiber -scheduler & -queue and it can steal jobs from other threads in the same pool. It also has a Job Batching system, so you can submit multiple jobs at a time and manage dependencies more efficiently.
- **ECS**, This is the next most funcdemental component, being the first API layer that you would likely actually use as a user. It adds the *Data Oriented Design* principles and applies the Job system for running ECS Systems.
- **Scenes**, this is the main component that makes the engine what it is, it contains the code for loading and unloading dynamic libraries and parsing and using them as asset(s), sub-engine(s) or scene(s) (techinically only game logic to use in a scene, though close engough). It of course also has the scene(s), either sequentially or concurrently, while allowing inter-scene communication through the `Event System` and reuse of the ECS context.
- **Event system**, this is the final component of the main architecture, allowing the concurrent processes and systems to share and pass data around and signal for inter process dependancies. This way the systems can run concurrent and define a process that must have finished before hand, so the systems can have a priority and can run concurrectly without worying about a dependency system not having run yet, tough this should mostly be avoided since it can still sometimes cause concurrecy deadlocks. and because the Job system uses fibers, you can use a `wait-event` function which would `yeild` instead of blocking.

Aside from that the core also aupplies some basic code/components to use, these are:
- **Platform Macros** for conditional compilation and for abstracting platform or compiler specific keywords into the same macro in `std.h`.
- **Error, warning and message logging**, for setting and getting errors (wont print unless `NXS_LogSetOutFile(stdout);` or `NXS_LogSetOutFile(stderr);` is called).
- **x86 & arm SIMD abstraction** for 128, 256 and 512 bit vectorized and 16 bit floating point operations with a software implementation for on systems without dedicated hardware support
- **Math**, linear algebra code that internally uses the SIMD lib for vectorized calculation.
- **Disk IO**, for reading from and writing to the disk, for save files, settings and other data that should persist after the app has quit.
- **Time**, for getting how long the app has been running, mastly for deltatime and FPS management.
- **Basic ECS Components**:
    - **Transform**, for relative and absolute *Position*, *Scale* and *Rotation* data. for use with `NXS_ChildrenComponent` and `NXS_ParentComponent`.
    - **Children**, for nesting ECS entities and setting relative transform values.
    - **Parent**, for tracing ECS entity nesting and relative transform values and access to a parent's data like components.
    - **Timer**, for activating/calling a callback after a set time or at a given time interval.
- **Basic ECS Systems**:
    - **Transform**, for updating children's transform components relative to that of their parent.
    - **Timer**, for updating/checking timer components and activating/calling the callback if the time or time until next interval has elapsed.
- **Encryption**, for (when possible, hardware accelerated) binary excryption. Mainly for encrypting the dynamic libraries and thus assets and logic/code, to counter decompilation and asset stripping (though likely at a slight performance cost).

<!-- TODO: ### IDE -->

## Features

### Core Utilities & Architecture
The Core module provides the base architecture and a set of essential utilities:

- **Concurrency:** Job System with thread and fiber pools for concurrent processing.
- **Data-Oriented Design (DOD):** Entity Component System (ECS) for efficient, cache friendly data layout.
- **Modularity:** Dynamic scene and library loading system for modular sub-engines and component swapping.
- **Low Level Optimization:** Built in SIMD abstraction for vectorized linear algebra and math operations.
- **Basic Components:** Built in ECS components for **Transform**, **Parent/Child nesting**, and **Timer** functionality.

<!-- ### Framework
- Display
- GPU
- Input
- Network
- Physics
- Scripting -->

<!-- ### IDE
- ... -->

<!-- ### Performance
TODO: show banchmarks -->

### TODO
<!-- maybe add a little more detail -->
See [`TODO.md`](./TODO.md).

Though there are probably always still [`SIMD`](./Framework/Core/inc/SIMD/) functions left to implement.

## Contributing
All contributions of any kind are welcome, and all contributions are appreciated.

To begin contributing, I'd recommend the following few steps to make sure you follow conventions (so the repo does not become a mess) and that you are not doing the same thing someone else is already doing:

1.  **Find an Issue:** Look for an issue you'd like to work on in the GitHub Issues page. Issues with the `good first issue` label are a great place to start.
2.  **Assign Yourself:** To let others know you're working on it, assign yourself to the issue on GitHub.
3.  **Create a Branch:** Create a new branch with a name that reflects the issue number and a brief description (e.g., `fix-vulkan-tearing-#53`).
4.  **Work on a Solution:** Write your code, documentation, or tests.
5.  **Open a Pull Request:** When you're ready, open a new pull request and link it to the issue by including `Fixes #53` or `Closes #53` in the description.

Though for more details, please read [contributing](./CONTRIBUTING.md).

## Documentation
The documentation, when made, will appear [here](./Docs/).

## Usage
Note: not much has been finished yet, this includes the build system, which probably doesnt work yet.

see [API Docs](./Docs/api_index.md).
see [IDE Docs](./Docs/ide.md).
<!-- 
### Platforms
- Linux
- Windows
- Android
- ... -->
### System Requirments
- x86 or arm CPU 32 or 64 bit
- Multiple cores prefered
- SIMD support prefered (SSE, SSE2, SSE3, SE4.1, SSE4.2, AVX, AVX2, NEON, SVE, SME)

### Dependencies
- [SDL3](https://github.com/libsdl-org/SDL)

### Compiling
note: only supports gcc, clang and msvc, though gcc/clang is recomended (in cases like `nxis_float16_to_float32` actually results in faster code than MSVC).

- run a `build.*` file in a terminal, for help on options use `-h`or `--help`, though many wont work yet.

#### Prerequisites
- CMake
- (optional) Python (for `build.py`)
- GCC, CLang or MSVC
- optionally a C++ compiler like `g++`

### Examples
<!-- maybe add a little more detail -->
see [`EXAMPLES.md`](Examples/EXAMPLES.md).

<!-- ## API bindings
### Native (official)
| Language | Documentation                  | Source                                  |
|----------|--------------------------------|-----------------------------------------|
| C++      | [C++ API](Docs/API/C++/C++.md) | [Example API source](Framework/CppAPI/) | -->
<!-- ### Non Native (unofficial)
| Language | Link                            | Creator                        |
|----------|---------------------------------|--------------------------------|
| Java     | [NexisJava](github/project/url) | [some person](github/user/url) | -->

## Projects that use it
Right now there are no external projects using this engine yet, if you have one and want it to be shown here, please send and email to \<[chair.x86@gmail.com](chair.x86@gmail.com)\> or ask on the [Discord](https://discord.gg/e6dMFJfGXN).

## Reporting Issues
Please do so through Github issues.

## Licence
The Nexis Engine is licensed under the MIT license. see [`LICENSE.md`](./LICENSE).
