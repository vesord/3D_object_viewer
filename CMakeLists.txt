cmake_minimum_required(VERSION 3.19)
project(scop C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -lGL)
#-lpthread -lXrandr -lXi

include_directories(glew-2.2.0/include)
include_directories(glfw-3.3.4/include)
#target_link_directories(glew-2.2.0/lib glfw-3.3.4/src)

add_executable(scop srcs/main.c)

target_link_libraries(scop ${CMAKE_SOURCE_DIR}/glew-2.2.0/lib/libGLEW.a ${CMAKE_SOURCE_DIR}/glfw-3.3.4/src/libglfw3.a GL X11 pthread m dl  )