cmake_minimum_required(VERSION 3.19)
project(scop C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS)


#IF (APPLE)
#	SET(GCC_COVERAGE_COMPILE_FLAGS "")
#	SET(GCC_COVERAGE_LINK_FLAGS "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
#	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINK_FLAGS}")
#ENDIF()

#add_link_options("-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

set(CMAKE_C_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

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
include_directories(srcs/initialization)
include_directories(srcs/display)
include_directories(srcs/bmp_load)

set(MAIN_FILES  srcs/scop.h
				srcs/types.h
				srcs/scop_struct.h
				srcs/main.c )
set(CALCULATIONS_FILES  srcs/calculations/calculations.h
						srcs/calculations/calculations.c
	srcs/parsing/calc_center_offset.c
						srcs/calculations/calc_matrices.c)

set(DISPLAY_FILES   srcs/display/display.h
					srcs/display/display.c)
set(EVENTS_FILES    srcs/events/events.h
					srcs/events/events_private.h
					srcs/events/callbacks.c
					srcs/events/key_actions.c
					srcs/events/terminal.c)
set(PARSING_FILES   srcs/parsing/parsing.h
					srcs/parsing/parsing_private.h
					srcs/parsing/parse_obj.c
					srcs/parsing/parsing_utils.c
					srcs/parsing/line_type_parsers.c
					srcs/parsing/saving_buffers.c
					srcs/parsing/fill_output_data.c
					srcs/parsing/bmp_load.h
					srcs/parsing/bmp_load.c)
set(SHADERS_FILES   srcs/shaders/shaders.h
					srcs/shaders/shader_private.h
					srcs/shaders/shaders.c
					srcs/shaders/shaders_utils.c)

set(BUFFERS_FILES   srcs/buffers/buffers.h
					srcs/buffers/buffers.c)

set(INIT_FILES      srcs/initialization/initialization.h
					srcs/initialization/initialization_private.h
					srcs/initialization/initialization.c
					srcs/initialization/init_system.c
					srcs/initialization/init_view.c
					srcs/initialization/init_matrices.c
					srcs/initialization/init_scop.c)

add_executable(scop ${MAIN_FILES}
					${CALCULATIONS_FILES}
					${DISPLAY_FILES}
					${EVENTS_FILES}
					${PARSING_FILES}
					${SHADERS_FILES}
					${BUFFERS_FILES}
					${INIT_FILES})

target_link_libraries(scop  ${CMAKE_SOURCE_DIR}/glew-2.2.0/lib/libGLEW.a
							${CMAKE_SOURCE_DIR}/glfw-3.3.4/src/libglfw3.a
							${CMAKE_SOURCE_DIR}/libft/libft.a)

IF(UNIX AND NOT APPLE)
	target_link_libraries(scop GL X11 pthread m dl)
ENDIF()