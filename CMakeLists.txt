# Copyright (c) 2024 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET lab3)

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})

add_subdirectory(${MBED_PATH})
# add_subdirectory(${CMAKE_SOURCE_DIR}/src)
# add_subdirectory(${CMAKE_SOURCE_DIR}/include)

add_executable(${APP_TARGET} main.cpp src/adxl.cpp src/tmp.cpp)

# Add your source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

target_include_directories(${APP_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add your include directories
#include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# target_sources(${APP_TARGET}
#     PRIVATE
#         ${SOURCES}
        
# )

# add_executable(
#     ${APP_TARGET} 
#     ${SOURCES}
#     # src/tmp.cpp
#     # src/adxl.cpp
#     # include/adxl.h 
#     # include/tmp.h
# )

# target_sources(${APP_TARGET} PRIVATE main.cpp)

target_link_libraries(${APP_TARGET} mbed-os)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()