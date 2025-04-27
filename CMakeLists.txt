
cmake_minimum_required(VERSION 3.14) # Ensure we have a recent CMake version
project(SoyLuna)

# Include FetchContent module
include(FetchContent)

# Declare raylib dependency
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0)  # You can specify the version you want

# Disable raylib examples and testing
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

# Make raylib available
FetchContent_MakeAvailable(raylib)

# Add your executable
add_executable(${PROJECT_NAME} main.c)

# Link raylib with your executable
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# If you're on Windows and using MinGW, you might need these
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()