cmake_minimum_required(VERSION 3.19)
project(scop C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS)
#-lpthread -lXrandr -lXi

include_directories(glew-2.2.0/include)
include_directories(glfw-3.3.4/include)
include_directories(srcs)
include_directories(srcs/shaders)
include_directories(srcs/calculations)

#target_link_directories(glew-2.2.0/lib glfw-3.3.4/src)

set(MAIN_FILES srcs/main.c srcs/scop.h)
set(CALCULATIONS_FILES  srcs/calculations/calculations.h
						srcs/calculations/rotationOffset.c)

set(DISPLAY_FILES)
set(EVENTS_FILES)
set(PARSING_FILES)
set(SHADERS_FILES   srcs/shaders/shaders.h
					srcs/shaders/shaders.c)

add_executable(scop ${MAIN_FILES}
					${CALCULATIONS_FILES}
					${DISPLAY_FILES}
					${ENENTS_FILES}
					${PARSING_FILES}
					${SHADERS_FILES})

target_link_libraries(scop ${CMAKE_SOURCE_DIR}/glew-2.2.0/lib/libGLEW.a ${CMAKE_SOURCE_DIR}/glfw-3.3.4/src/libglfw3.a GL X11 pthread m dl  )