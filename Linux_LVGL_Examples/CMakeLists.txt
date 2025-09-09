cmake_minimum_required(VERSION 3.10)
project(LVGL_Application)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

option(ARM "Build for ARM architecture" OFF)
option(SDL "Build for SDL Libraries" OFF)
if(ARM)
    add_compile_definitions(ARM=1)
endif()

if(ARM)
set(TOOLCHAIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Cross_Compiler/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf")
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/bin/arm-none-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/bin/arm-none-linux-gnueabihf-g++")
endif()

# find_package(Threads REQUIRED)

# Add LVGL, SDL, and driver files
include_directories(lvgl)
include_directories(lvgl/src)
include_directories(lv_drivers)


if(SDL)
    add_compile_definitions(USE_SDL=1)
    add_compile_definitions(SDL_FLAG=1)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

# Add source files
set(SOURCES main.cpp)

# Add LVGL source files
file(GLOB_RECURSE LVGL_SOURCES lvgl/src/*.c)

# Add SDL driver source files
file(GLOB_RECURSE LV_DRV_SOURCES lv_drivers/*.c)

# Add BMO driver source files
file(GLOB_RECURSE BMO_DRV_SOURCES bmo_interface/*.c)

# Create executable
add_executable(LVGL_Linux_Example ${SOURCES} ${LVGL_SOURCES} ${LV_DRV_SOURCES} ${BMO_DRV_SOURCES})

if(SDL)
    target_link_libraries(LVGL_Linux_Example SDL2 SDL2main pthread)
else()
    target_link_libraries(LVGL_Linux_Example pthread)
endif()
