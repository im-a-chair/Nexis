@echo off
setlocal enabledelayedexpansion

rem --- Arguments ---

rem check cmake presence
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: cmake is not installed. Aborting. >&2
    exit /b 1
)

set BUILD_TARGET=
set SKIP_LIB=false
set SKIP_CLI=false
set INSTALL=false
set INSTALL_PREFIX=
set BUILD_TYPE=debug
set PLATFORM=
set ARCHITECTURE=
set OPTIMIZATION_LEVEL=0

for /f "tokens=1,*" %%a in ('echo %*') do (
    set "param=%%a"
    if /i "!param!" == "-h" (
        call :usage
        exit /b 0
    )
    if /i "!param!" == "/h" (
        call :usage
        exit /b 0
    )
    if /i "!param!" == "--help" (
        call :usage
        exit /b 0
    )
    if /i "!param!" == "-l" (
        set SKIP_LIB=true
    )
    if /i "!param!" == "/l" (
        set SKIP_LIB=true
    )
    if /i "!param!" == "--no-lib" (
        set SKIP_LIB=true
    )
    if /i "!param!" == "-c" (
        set SKIP_CLI=true
    )
    if /i "!param!" == "/c" (
        set SKIP_CLI=true
    )
    if /i "!param!" == "--no-cli" (
        set SKIP_CLI=true
    )
    if /i "!param!" == "-i" (
        set INSTALL=true
    )
    if /i "!param!" == "/i" (
        set INSTALL=true
    )
    if /i "!param!" == "--install" (
        set INSTALL=true
    )
    if /i "!param!" == "-d" (
        set BUILD_TYPE=debug
    )
    if /i "!param!" == "/d" (
        set BUILD_TYPE=debug
    )
    if /i "!param!" == "--debug" (
        set BUILD_TYPE=debug
    )
    if /i "!param!" == "-r" (
        set BUILD_TYPE=release
    )
    if /i "!param!" == "/r" (
        set BUILD_TYPE=release
    )
    if /i "!param!" == "--release" (
        set BUILD_TYPE=release
    )
    if /i "!param!" == "-p" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set INSTALL=true
        set INSTALL_PREFIX=%%b
    )
    if /i "!param!" == "/p" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set INSTALL=true
        set INSTALL_PREFIX=%%b
    )
    if /i "!param!" == "--prefix" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set INSTALL=true
        set INSTALL_PREFIX=%%b
    )
    if /i "!param!" == "-s" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set PLATFORM=%%b
    )
    if /i "!param!" == "/s" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set PLATFORM=%%b
    )
    if /i "!param!" == "--platform" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set PLATFORM=%%b
    )
    if /i "!param!" == "-a" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set ARCHITECTURE=%%b
    )
    if /i "!param!" == "/a" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set ARCHITECTURE=%%b
    )
    if /i "!param!" == "--arch" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set ARCHITECTURE=%%b
    )
    if /i "!param!" == "-O" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set OPTIMIZATION_LEVEL=%%b
    )
    if /i "!param!" == "/O" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set OPTIMIZATION_LEVEL=%%b
    )
    if /i "!param!" == "--optimize" (
        if "%%b"=="" (
            echo Error: Argument for %param% cannot be empty. >&2
            exit /b 1
        )
        set OPTIMIZATION_LEVEL=%%b
    )
    if /i "!param!" == "ide" (
        set BUILD_TARGET=ide
    )
    if /i "!param!" == "cli" (
        set BUILD_TARGET=cli
    )
    if /i "!param!" == "lib" (
        set BUILD_TARGET=lib
    )
)

if "!BUILD_TARGET!"=="" (
    echo No build target (ide^|cli^|lib) specified. >&2
    call :usage >&2
    exit /b 1
)

rem --- Main ---

if "!BUILD_TARGET!"=="lib" (
    if "!SKIP_LIB!"=="true" (
        echo Warning: Incompatible args: 'lib' target with --no-lib flag.
        echo Nothing to do, exiting...
        exit /b 1
    )
    call :build_lib
) else if "!BUILD_TARGET!"=="cli" (
    if "!SKIP_CLI!"=="true" (
        echo Warning: Incompatible args: 'cli' target with --no-cli flag.
        echo Nothing to do, exiting...
        exit /b 1
    )
    if "!SKIP_LIB!"=="false" (
        echo Building dependencies (libraries)...
        call :build_lib
    )
    call :build_cli
) else if "!BUILD_TARGET!"=="ide" (
    if "!SKIP_LIB!"=="false" (
        echo Building dependencies (libraries)...
        call :build_lib
    )
    if "!SKIP_CLI!"=="false" (
        echo Building dependencies (CLI)...
        call :build_cli
    )
    call :build_ide
)

exit /b 0

:usage
echo.
echo Usage: %~nx0 ^<ide^|cli^|lib^>
echo        [--no-lib] [--no-cli] [--install] [--debug^|--release] [--prefix ^<path^>]
echo        [--platform ^<platform^>] [--arch ^<arch^>] [--optimize ^<level^>]
echo.
echo Builds the Nexis engine components with CMake.
echo.
echo Options:
echo   -h, /h, --help           Show this help message and exit.
echo   -l, /l, --no-lib         Do not build the framework libraries (if not needed).
echo   -c, /c, --no-cli         Do not build the CLI executable (if not needed).
echo   -i, /i, --install        Install the built binaries.
echo   -p, /p, --prefix ^<path^>  Path to install at
echo   -d, /d, --debug          Build in debug mode ^(default is release^).
echo   -r, /r, --release        Build in release mode.
echo   -s, /s, --platform ^<os^>  Target platform ^(e.g., windows, linux, android^).
echo   -a, /a, --arch ^<arch^>    Target architecture ^(e.g., x64, arm^).
echo   -O, /O, --optimize ^<level^> Compiler optimization level ^(e.g., 0, 1, 2, 3^).
echo.
exit /b 0

:create_dirs
mkdir build\%1\%BUILD_TYPE%\%PLATFORM%\%ARCHITECTURE%
cd build\%1\%BUILD_TYPE%\%PLATFORM%\%ARCHITECTURE%
exit /b 0

:run_cmake
echo Running CMake for the %1 target...
echo   - CWD: %CD%
echo   - BUILD_TYPE: %BUILD_TYPE%
echo   - PLATFORM: %PLATFORM%
echo   - ARCHITECTURE: %ARCHITECTURE%
echo   - OPTIMIZATION_LEVEL: %OPTIMIZATION_LEVEL%
echo   - INSTALL: %INSTALL%
if not "%INSTALL_PREFIX%"=="" (
    echo   - INSTALL_PREFIX: %INSTALL_PREFIX%
)

cmake -S "..\..\%1" -B . ^
      -DCMAKE_BUILD_TYPE="%BUILD_TYPE%" ^
      -DPLATFORM="%PLATFORM%" ^
      -DARCHITECTURE="%ARCHITECTURE%" ^
      -DOPTIMIZATION_LEVEL="%OPTIMIZATION_LEVEL%"
if %errorlevel% neq 0 (
    echo CMake configure and build failed.
    exit /b 1
)

if "!INSTALL!"=="true" (
    echo Installing...
    if not "%INSTALL_PREFIX%"=="" (
        cmake --install . --config "%BUILD_TYPE%" --prefix "%INSTALL_PREFIX%"
    ) else (
        cmake --install . --config "%BUILD_TYPE%"
    )
    if %errorlevel% neq 0 (
        echo Installation failed.
        exit /b 1
    )
)
exit /b 0

:build_lib
echo Building the framework libraries...
call :create_dirs Framework
call :run_cmake Framework
exit /b 0

:build_cli
echo Building the CLI executable...
call :create_dirs CLI
call :run_cmake CLI
exit /b 0

:build_ide
echo Building the IDE...
call :create_dirs IDE
call :run_cmake IDE
exit /b 0