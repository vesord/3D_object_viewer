cmake_minimum_required(VERSION 3.19)
project(scop C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS)
#-lpthread -lXrandr -lXi

include_directories(glew-2.2.0/include)
include_directories(glfw-3.3.4/include)
include_directories(libft)
include_directories(srcs)
include_directories(srcs/shaders)
include_directories(srcs/calculations)
include_directories(srcs/parsing)
include_directories(srcs/events)
include_directories(srcs/buffers)

#target_link_directories(glew-2.2.0/lib glfw-3.3.4/src)

set(MAIN_FILES  srcs/scop.h
				srcs/types.h
				srcs/main.c )
set(CALCULATIONS_FILES  srcs/calculations/calculations.h
	srcs/calculations/calculations.c)

set(DISPLAY_FILES)
set(EVENTS_FILES    srcs/events/events.h
					srcs/events/events_private.h
					srcs/events/callbacks.c)
set(PARSING_FILES   srcs/parsing/parsing.h
					srcs/parsing/parsing_private.h
					srcs/parsing/parse_obj.c
					srcs/parsing/parsing_utils.c
					srcs/parsing/line_type_parsers.c
					srcs/parsing/saving_buffers.c
					srcs/parsing/fill_output_buffers.c)
set(SHADERS_FILES   srcs/shaders/shaders.h
					srcs/shaders/shader_private.h
					srcs/shaders/shaders.c)

set(BUFFERS_FILES   srcs/buffers/buffers.h
					srcs/buffers/buffers.c)

add_executable(scop ${MAIN_FILES}
					${CALCULATIONS_FILES}
					${DISPLAY_FILES}
					${EVENTS_FILES}
					${PARSING_FILES}
					${SHADERS_FILES}
					${BUFFERS_FILES})

target_link_libraries(scop  ${CMAKE_SOURCE_DIR}/glew-2.2.0/lib/libGLEW.a
							${CMAKE_SOURCE_DIR}/glfw-3.3.4/src/libglfw3.a
							${CMAKE_SOURCE_DIR}/libft/libft.a
							GL X11 pthread m dl  )