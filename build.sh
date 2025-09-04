#!/bin/bash

# make `-l, --no-lib` and `-c, --no-cli` into `-n, --no <cli|lib>`
# add `-x, --SIMD <SSE|SSE2|SSE3|SSE4.1|SSE4.2|AVX|AVX2|AVX512|NEON|SVE|SME>`
# add `-t, --threads <count>` to set `NXS_THREAD_COUNT`
# add `-n, --native` for native settings, e.g. for debug
# add `-C, --compiler <compiler|path>` -- will fail if not found
# add `-L, --linker <linker|path>` -- will fail if not found
# add `-A, --assembler <assembler|path>` -- will fail if not found
# add `-o, --outdir <dir>`
# add `-v, --version`

set -euo pipefail

usage() {
    echo ""
    echo "Usage: $(basename "$0") <ide|cli|lib>"
    echo "       [--no-lib] [--no-cli] [--install] [--debug|--release] [--prefix <path>]"
    echo "       [--platform <platform>] [--arch <arch>] [--optimize <level>]"
    echo ""
    echo "Builds the Nexis engine components with CMake."
    echo ""
    echo "Options:"
    echo "  -h, --help               Show this help message and exit."
    echo "  -l, --no-lib             Do not build the framework libraries (if not needed)."
    echo "  -c, --no-cli             Do not build the CLI executable (if not needed)."
    echo "  -i, --install            Install the built binaries."
    echo "  -p, --prefix <path>      Path to install at"
    echo "  -d, --debug              Build in debug mode (default is release)."
    echo "  -r, --release            Build in release mode."
    echo "  -s, --platform <os>      Target platform (e.g., windows, linux, android)."
    echo "  -a, --arch <arch>        Target architecture (e.g., x64, arm)."
    echo "  -O, --optimize <level>   Compiler optimization level (e.g., 0, 1, 2, 3)."
    echo ""
}

# --- Arguments ---

command -v cmake >/dev/null 2>&1 || { echo >&2 "Error: cmake is not installed. Aborting."; exit 1; }

BUILD_TARGET=""
SKIP_LIB=false
SKIP_CLI=false
INSTALL=false
INSTALL_PREFIX=""
BUILD_TYPE="debug"
PLATFORM=""
ARCHITECTURE=""
OPTIMIZATION_LEVEL="0"

while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help)
            usage
            exit 0
            ;;
        -l|--no-lib)
            SKIP_LIB=true
            ;;
        -c|--no-cli)
            SKIP_CLI=true
            ;;
        -i|--install)
            INSTALL=true
            ;;
        -d|--debug)
            BUILD_TYPE="debug"
            ;;
        -r|--release)
            BUILD_TYPE="release"
            ;;
        -p|--prefix)
            if [ -z "${2:-}" ]; then
                echo "Error: Argument for $1 cannot be empty." >&2
                exit 1
            fi
            INSTALL=true
            INSTALL_PREFIX="$2"
            shift
            ;;
        -s|--platform)
            PLATFORM="$2"
            shift
            ;;
        -a|--arch)
            ARCHITECTURE="$2"
            shift
            ;;
        -O|--optimize)
            OPTIMIZATION_LEVEL="$2"
            shift
            ;;
        ide|cli|lib)
            BUILD_TARGET="$1"
            ;;
        *)
            echo "Unknown argument: $1" >&2
            exit 1
            ;;
    esac
    shift
done

if [ -z "$BUILD_TARGET" ]; then
    echo "No build target (ide|cli|lib) specified." >&2
    usage >&2
    exit 1
fi

# --- Main ---

create_dirs() {
    mkdir -p "./build/${1}/${BUILD_TYPE}/${PLATFORM}/${ARCHITECTURE}"
    cd "./build/${1}/${BUILD_TYPE}/${PLATFORM}/${ARCHITECTURE}"
}

run_cmake() {
    echo "Running CMake for the ${1} target..."
    echo "  - CWD: $(pwd)"
    echo "  - BUILD_TYPE: ${BUILD_TYPE}"
    echo "  - PLATFORM: ${PLATFORM}"
    echo "  - ARCHITECTURE: ${ARCHITECTURE}"
    echo "  - OPTIMIZATION_LEVEL: ${OPTIMIZATION_LEVEL}"
    echo "  - INSTALL: ${INSTALL}"
    if [ -n "$INSTALL_PREFIX" ]; then
        echo "  - INSTALL_PREFIX: ${INSTALL_PREFIX}"
    fi

    # config & build
    cmake -S "../../../../${1}" -B . \
      -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
      -DPLATFORM="${PLATFORM}" \
      -DARCHITECTURE="${ARCHITECTURE}" \
      -DOPTIMIZATION_LEVEL="${OPTIMIZATION_LEVEL}"

    echo "Building..."
    cmake --build .

    # install
    if [ "$INSTALL" = true ]; then
        echo "Installing..."
        cmake --install . --config "${BUILD_TYPE}" --prefix "$INSTALL_PREFIX"
    fi
}

build_lib() {
    echo "Building the framework libraries..."
    create_dirs "Framework"
    run_cmake "Framework"
}

build_cli() {
    echo "Building the CLI executable..."
    create_dirs "CLI"
    run_cmake "CLI"
}

build_ide() {
    echo "Building the IDE..."
    create_dirs "IDE"
    run_cmake "IDE"
}

case "$BUILD_TARGET" in
    lib)
        if [ "$SKIP_LIB" = true ]; then
            echo "Warning: Incompatible args: 'lib' target with --no-lib flag."
            echo "Nothing to do, exiting..."
            exit 1
        fi
        build_lib
        ;;
    cli)
        if [ "$SKIP_CLI" = true ]; then
            echo "Warning: Incompatible args: 'cli' target with --no-cli flag."
            echo "Nothing to do, exiting..."
            exit 1
        fi
        if [ "$SKIP_LIB" = false ]; then
            echo "Building dependencies (libraries)..."
            build_lib
        fi
        build_cli
        ;;
    ide)
        if [ "$SKIP_LIB" = false ]; then
            echo "Building dependencies (libraries)..."
            build_lib
        fi
        if [ "$SKIP_CLI" = false ]; then
            echo "Building dependencies (CLI)..."
            build_cli
        fi
        build_ide
        ;;
esac