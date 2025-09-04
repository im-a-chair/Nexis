import os
import sys
import subprocess
import argparse

def usage():
    """Prints the usage message."""
    print(f"Usage: {os.path.basename(sys.argv[0])} <ide|cli|lib>")
    print("       [--no-lib] [--no-cli] [--install] [--debug|--release] [--prefix <path>]")
    print("       [--platform <platform>] [--arch <arch>] [--optimize <level>]")
    print("\nBuilds the Nexis engine components with CMake.")
    print("\nOptions:")
    print("  -h, /h, --help           Show this help message and exit.")
    print("  -l, /l, --no-lib         Do not build the framework libraries (if not needed).")
    print("  -c, /c, --no-cli         Do not build the CLI executable (if not needed).")
    print("  -i, /i, --install        Install the built binaries.")
    print("  -p, /p, --prefix <path>  Path to install at")
    print("  -d, /d, --debug          Build in debug mode (default is release).")
    print("  -r, /r, --release        Build in release mode.")
    print("  -s, /s, --platform <os>  Target platform (e.g., windows, linux, android).")
    print("  -a, /a, --arch <arch>    Target architecture (e.g., x64, arm).")
    print("  -O, /O, --optimize <level> Compiler optimization level (e.g., 0, 1, 2, 3).")

def create_dirs(target_name, args):
    """Creates the build directories and changes the current working directory."""
    path = os.path.join("build", target_name, args.build_type, args.platform, args.arch)
    os.makedirs(path, exist_ok=True)
    os.chdir(path)

def run_cmake(target_name, args):
    """Runs CMake to configure, build, and install the specified target."""
    print(f"Running CMake for the {target_name} target...")
    print(f"  - CWD: {os.getcwd()}")
    print(f"  - BUILD_TYPE: {args.build_type}")
    print(f"  - PLATFORM: {args.platform}")
    print(f"  - ARCHITECTURE: {args.arch}")
    print(f"  - OPTIMIZATION_LEVEL: {args.optimize}")
    print(f"  - INSTALL: {args.install}")
    if args.prefix:
        print(f"  - INSTALL_PREFIX: {args.prefix}")

    # configure
    config_cmd = [
        "cmake",
        f"-S./../../../../../{target_name}",
        "-B.",
        f"-DCMAKE_BUILD_TYPE={args.build_type}",
        f"-DPLATFORM={args.platform}",
        f"-DARCHITECTURE={args.arch}",
        f"-DOPTIMIZATION_LEVEL={args.optimize}"
    ]
    if subprocess.run(config_cmd).returncode != 0:
        print("CMake configure failed.", file=sys.stderr)
        sys.exit(1)

    # build
    print("Building...")
    config_cmd = [
        "cmake",
        f"--build",
        f"."
    ]
    if subprocess.run(config_cmd).returncode != 0:
        print("CMake build failed.", file=sys.stderr)
        sys.exit(1)

    # install
    if args.install:
        print("Installing...")
        install_cmd = ["cmake", "--install", ".", "--config", args.build_type]
        if args.prefix:
            install_cmd.extend(["--prefix", args.prefix])
        
        if subprocess.run(install_cmd).returncode != 0:
            print("Installation failed.", file=sys.stderr)
            sys.exit(1)

def build_lib(args):
    """Builds the framework libraries."""
    print("Building the framework libraries...")
    create_dirs("Framework", args)
    run_cmake("Framework", args)

def build_cli(args):
    """Builds the CLI executable."""
    print("Building the CLI executable...")
    create_dirs("CLI", args)
    run_cmake("CLI", args)

def build_ide(args):
    """Builds the IDE."""
    print("Building the IDE...")
    create_dirs("IDE", args)
    run_cmake("IDE", args)

if __name__ == "__main__":
    # check cmake presence
    try:
        subprocess.run(["cmake", "--version"], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except FileNotFoundError:
        print("Error: cmake is not installed. Aborting.", file=sys.stderr)
        sys.exit(1)

    parser = argparse.ArgumentParser(
        description="Builds the Nexis engine components with CMake.",
        prefix_chars="-/"
    )
    parser.add_argument("target", choices=["ide", "cli", "lib"], help="The component to build.")
    parser.add_argument("-l", "--no-lib", action="store_true", help="Do not build the framework libraries.")
    parser.add_argument("-c", "--no-cli", action="store_true", help="Do not build the CLI executable.")
    parser.add_argument("-i", "--install", action="store_true", help="Install the built binaries.")
    parser.add_argument("-p", "--prefix", help="Path to install at. Implies --install.")
    parser.add_argument("-d", "--debug", dest="build_type", action="store_const", const="debug", default="debug", help="Build in debug mode (default).")
    parser.add_argument("-r", "--release", dest="build_type", action="store_const", const="release", help="Build in release mode.")
    parser.add_argument("-s", "--platform", help="Target platform (e.g., windows, linux, android).")
    parser.add_argument("-a", "--arch", help="Target architecture (e.g., x64, arm).")
    parser.add_argument("-O", "--optimize", default="0", help="Compiler optimization level (e.g., 0, 1, 2, 3).")

    args = parser.parse_args()

    # the --prefix flag implies --install
    if args.prefix:
        args.install = True

    # main build logic
    if args.target == "lib":
        if args.no_lib:
            print("Warning: Incompatible args: 'lib' target with --no-lib flag.")
            print("Nothing to do, exiting...")
            sys.exit(1)
        build_lib(args)

    elif args.target == "cli":
        if args.no_cli:
            print("Warning: Incompatible args: 'cli' target with --no-cli flag.")
            print("Nothing to do, exiting...")
            sys.exit(1)
        if not args.no_lib:
            print("Building dependencies (libraries)...")
            build_lib(args)
        build_cli(args)

    elif args.target == "ide":
        if not args.no_lib:
            print("Building dependencies (libraries)...")
            build_lib(args)
        if not args.no_cli:
            print("Building dependencies (CLI)...")
            build_cli(args)
        build_ide(args)