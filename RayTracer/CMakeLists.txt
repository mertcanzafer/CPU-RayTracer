# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(RayTracer VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(header)

# Specify the source files
file(GLOB SRC_FILES "src/*.cpp")

# Add the executable target
add_executable(RayTracer ${SRC_FILES})

# Find and link the SDL2 library
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(RayTracer ${SDL2_LIBRARIES})

# Add compile options
target_compile_options(RayTracer PRIVATE -g)

# Custom clean target
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
    DEPENDS clean
)

# Create a custom clean-all script
file(WRITE ${CMAKE_BINARY_DIR}/clean-all.cmake
"file(GLOB_RECURSE files \"\${CMAKE_BINARY_DIR}/*\")
foreach(file \${files})
    file(REMOVE \${file})
endforeach()")

# Custom clean command
add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt ${CMAKE_BINARY_DIR}/Makefile
)
