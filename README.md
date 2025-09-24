<!-- [![Build Status](https://img.shields.io/github/actions/workflow/status/im-a-chair/Nexis/main.yml?branch=main)](https://github.com/im-a-chair/Nexis/actions?query=workflow%3Amain)-->
[![License](https://img.shields.io/badge/license-MIT-orange.svg)](./LICENSE.md)
[![Version](https://img.shields.io/badge/version-v1.0-brightgreen.svg)]()

# Nexis Game Engine

<!-- logo & title banner -->
<!-- <br> -->

The Nexis Game Engine is a game engine that aims to, besides being modular, offer both a text based and a GUI based approach to game making and a way to easially switch between them.

### Design & Goal/Aim

The Nexis Game Engine came forth out of a frustration with game engines like Unity and Godot. Where for nearly everything, both the GUI/IDE and scripting are required. I myself as a programmer really prefer plain text based workflow, but other team members like artists, directors and designers tend to prefer the GUI based workflow. Thus I decided "I'll just make my own game engine". With the goal of making an engine that offers the option to both, work in text and work in the GUI, and most of all switch whenever you feel like it.

With this a few main problems came to mind:
- When having a text based project, the folder and file structer is way less predictable. So how does the GUI know what and where in the game
    - ...
- How will i make a full game engine as a solo dev
    - ...
- ...
    - ...

## Features
- an optional GUI that is not required but simply a tool to use when you feel like it, allowing you to switch between IDE based and text based whenever you feel like it
    - allows both a low level control and a engineer friendly text based environment and a visual designer friendly environment to be used alongside each other and to switch anytime
- dynamic library based scene loading
    - allows hot reloading
- very modular components like physics, rendering or input
### Performance
- mention SIMD and other optimization efforts
- show results
- comparison of different parts to camparable projects
### TODO
<!-- maybe add a little more detail -->
see [`TODO.md`](./TODO.md).

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
- Code & Folder Structure (with link to code formatting standard md page)
- IDE usage docs
- CLI usage docs
- API
- Internal
- Tutorial

## Usage
Note: near nothing has been finished, this includes the build system, which probably doesnt work yet.

see [API Docs](./Docs/api_index.md)
see [CLI Docs]()
see [IDE Docs]()
### Platforms
- Linux
- Windows
- Android
- ...
### System Requirments
- x86 or arm CPU 32 or 64 bit
- Multiple cores prefered
- SIMD support prefered (SSE, SSE2, SSE3, SE4.1, SSE4.2, AVX, AVX2, NEON, SVE, SME)

### Dependencies
- SDL3

### Compiling
note: gcc | clang recomended (in cases like `nxis_float16_to_float32` actually results in faster code than MSVC)
- run a `build.*` file, for options use `-h`or `--help`, though many wont work yet.

#### Prerequisites
- CMake
- (optional) Python (for `build.py`)
- a C (and probably C++) Compiler

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
