@echo off
REM Build script for Windows (MinGW) using CMake
REM Usage: build.bat [Debug|Release]  (default: Debug)
if "%~1"=="" (
  set BUILD_TYPE=Debug
) else (
  set BUILD_TYPE=%~1
)
if not exist build mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DSFML_DIR="C:/Path/To/SFML/lib/cmake/SFML" ..
cmake --build . --config %BUILD_TYPE%
cd ..
pause
