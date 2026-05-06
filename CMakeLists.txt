cmake_minimum_required(VERSION 3.16)
project(RunProject VERSION 0.1 LANGUAGES CXX)

# Use a reasonably modern standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect sources from top-level .cpp files
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(Run ${SOURCES})

# Prefer SFML CMake targets (SFML 3+), fall back to library names.
find_package(SFML COMPONENTS graphics window system audio network)

if(TARGET SFML::Graphics)
  target_link_libraries(Run PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio SFML::Network)
else()
  target_link_libraries(Run PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
endif()

# Place runtime next to build dir
set_target_properties(Run PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# Helpful hints for MinGW/gcc on Windows
# Usage (example):
# mkdir build
# cd build
# cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DSFML_DIR="C:/Path/To/SFML/lib/cmake/SFML" ..
# cmake --build . --config Debug

# On Unix-like systems with gcc/clang, use the default generator:
# mkdir build && cd build
# cmake -DCMAKE_BUILD_TYPE=Release ..
# cmake --build .
