#!/usr/bin/env bash
# Build script for Unix-like systems (gcc/clang) using CMake
# Usage: ./build.sh [Release|Debug] (default: Release)
set -e
BUILD_TYPE=${1:-Release}
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
cmake --build . --config ${BUILD_TYPE}
echo "Build complete (type=${BUILD_TYPE})"
