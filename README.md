# Run (C++ SFML Demo)

Status: In development — work in progress.

Overview
- A small native C++ project using SFML for graphics, audio, and input.
- Purpose: demo/game prototype; not finished and under active development.

Structure (important folders/files)
- `Run.cpp`, other `*.cpp` / `*.h` source files
- `fonts/`, `graphics/`, `music/`, `shaders/`, `sound/` — assets
- `output/` — runtime output (ignored)
- Prebuilt DLLs and `Run.exe` may be present for convenience (ignored by `.gitignore`).

Requirements
- C++ toolchain (g++, clang, or MSVC)
- SFML 3.x installed (headers + libraries). On Windows, place SFML DLLs next to the executable or add SFML `bin` to PATH.

Build (example)
- VS Code: the workspace has a `Build with SFML (Debug)` task configured; use `Run Task...` → `Build with SFML (Debug)`.

- Manual build example (adjust SFML paths for your system):

```bash
cd Run
# example for g++ on Windows (MinGW) — update include/lib paths
g++ -g *.cpp -o Run.exe -I "D:/Program Files/SFML-3.0.2/include" -L "D:/Program Files/SFML-3.0.2/lib" \
  -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d -lsfml-network-d
```

CMake (MinGW / gcc)

If you prefer CMake (cross-platform) the project includes a `CMakeLists.txt` configured for use with MinGW/gcc. Example build steps:

```bash
cd Run
mkdir -p build
cd build
# Replace the SFML path below with your SFML install location
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DSFML_DIR="C:/Path/To/SFML/lib/cmake/SFML" ..
cmake --build . --config Debug
```

Notes:
- On Windows, ensure the SFML `bin` directory is on your `PATH` or copy required DLLs next to the executable in the build output directory.
- For Unix-like systems with gcc, use the default generator instead of `MinGW Makefiles`:

```bash
cd Run
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

Run
```bash
cd Run
./Run.exe
```

Notes
- The project includes SFML runtime DLLs for convenience; those are ignored via `Run/.gitignore` so they do not get committed.
- If you get missing DLL errors on Windows, ensure the SFML `bin` directory is on `PATH` or copy the required DLLs beside `Run.exe`.
- Remove compiled binaries (`*.exe`, `*.dll`) from the folder if you prefer building from source only.

Contributing
- This is experimental — open issues or PRs focused on individual subsystems (graphics, audio, input).
- Please keep changes small and document build steps if you add platform-specific requirements.

TODO (short)
- Add an automated build script (CMake or Makefile) for cross-platform builds.
- Document asset licensing and any external dependencies.

Local build scripts
- `build.bat`: Windows helper for MinGW/CMake (usage: `build.bat [Debug|Release]`, default `Debug`).
- `build.sh`: Linux / macOS helper for gcc/clang and CMake (usage: `./build.sh [Release|Debug]`, default `Release`).

Make `build.sh` executable on Linux/macOS before running:

```bash
cd Run
chmod +x build.sh
./build.sh
```
