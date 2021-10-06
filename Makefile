NAME = scop

# Sources with their directories
SRC_DIR = ./srcs

SRC_MAIN = main.c
INC_MAIN = scop.h scop_struct.h types.h

DIR_INITIALIZATION = initialization
SRC_INITIALIZATION = init_matrices.c init_scop.c init_system.c init_view.c initialization.c
INC_INITIALIZATION = initialization.h initialization_private.h

DIR_BUFFER = buffers
SRC_BUFFER = buffers.c
INC_BUFFER = buffers.h

DIR_CALCULATIONS = calculations
SRC_CALCULATIONS = calculations.c calc_matrices.c

DIR_DISPLAY = display
SRC_DISPLAY = display.c

DIR_EVENTS = events
SRC_EVENTS = callbacks.c key_actions.c terminal.c

DIR_PARSING = parsing
SRC_PARSING = bmp_load.c calc_center_offset.c fill_output_data.c line_type_parsers.c parse_obj.c parsing_utils.c saving_buffers.c

DIR_SHADERS = shaders
SRC_SHADERS = shaders.c shaders_utils.c


SRCS = 	$(SRC_MAIN) \
		$(addprefix $(DIR_INITIALIZATION)/, $(SRC_INITIALIZATION)) \
		$(addprefix $(DIR_BUFFER)/, $(SRC_BUFFER)) \
		$(addprefix $(DIR_CALCULATIONS)/, $(SRC_CALCULATIONS)) \
		$(addprefix $(DIR_DISPLAY)/, $(SRC_DISPLAY)) \
		$(addprefix $(DIR_EVENTS)/, $(SRC_EVENTS)) \
		$(addprefix $(DIR_PARSING)/, $(SRC_PARSING)) \
		$(addprefix $(DIR_SHADERS)/, $(SRC_SHADERS)) \
		$(addprefix $(OTHER_DIR), $(SRC_OTHER))

# libraries
# lGLEW
LIB_GLEW = ./glew-2.2.0/lib/libGLEW.a
LIB_DIR_GLEW = ./glew-2.2.0
LIB_PATH_GLEW =	./glew-2.2.0/lib
LIB_INCLUDE_GLEW = ./glew-2.2.0/include
# lglfw
LIB_GLFW = ./glfw-3.3.4/src/libglfw3.a
LIB_DIR_GLFW = ./glfw-3.3.4
LIB_PATH_GLFW =	./glfw-3.3.4/src
LIB_INCLUDE_GLFW =	./glfw-3.3.4/include
# libft
LIB_FT = ./libft/libft.a
LIB_INCLUDE_FT = ./libft
LIB_PATH_FT = ./libft
# lother
LIB_OTHER =
LIB_PATH_OTHER =
LIB_INCLUDE_OTHER =

LIBS = $(LIB_GLEW) $(LIB_GLFW) $(LIB_FT)
LIBS_PATH = $(LIB_PATH_GLEW) $(LIB_PATH_GLFW) $(LIB_PATH_FT) $(LIB_PATH_OTHER)
LIBS_INCLUDE = $(LIB_INCLUDE_GLEW) $(LIB_INCLUDE_GLFW) $(LIB_INCLUDE_FT) $(LIB_INCLUDE_OTHER)

#for linux GLEW glfw3 GL X11 pthread m dl ft
LIBS_LINK = ft GLEW glfw3 pthread m dl
#for macOS cocoa OpenGL IOKit CoreVideo
FRAMEWORKS = cocoa OpenGL IOKit

# Includes
INCLUDES =		$(LIBS_INCLUDE) \
				$(SRC_DIR) \
				$(addprefix $(SRC_DIR)/, $(DIR_BUFFER) \
                                     	 $(DIR_CALCULATIONS) \
                                     	 $(DIR_DISPLAY) \
                                     	 $(DIR_EVENTS) \
                                     	 $(DIR_INITIALIZATION) \
                                     	 $(DIR_PARSING) \
                                     	 $(DIR_SHADERS))

# Directory tree
DIRECTORIES = $(DIR_INITIALIZATION) $(DIR_BUFFER) $(DIR_DISPLAY) $(DIR_CALCULATIONS) $(DIR_SHADERS) $(DIR_PARSING) $(DIR_EVENTS)
OBJ_DIR = ./bin
OBJ_DIRECTORIES =	$(OBJ_DIR) \
					$(addprefix $(OBJ_DIR)/, $(DIRECTORIES))

# All object files
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Some necessary vars
CC = gcc
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter

.PHONY: all
all: $(OBJ_DIRECTORIES) $(NAME)
	@echo "\033[32mScop successfully built\033[0m"

$(OBJ_DIRECTORIES):
	@mkdir -p $(OBJ_DIRECTORIES)

$(NAME): $(LIBS) $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(addprefix -L./, $(LIBS_PATH)) $(addprefix -l, $(LIBS_LINK)) $(addprefix -framework , $(FRAMEWORKS)) -o $(NAME)

$(OBJECTS) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@/bin/echo -n $<
	@$(CC) $(FLAGS) $(addprefix -I./, $(INCLUDES)) -c $< -o $@
	@/bin/bash -c "echo -en \"\033[2K\033[0G\""
#include $(wildcard $(OBJ_DIR)/*.d $(OBJ_DIR)/*/*.d)

$(LIB_GLFW): $(LIB_DIR_GLFW)
	cd $(LIB_DIR_GLFW) && cmake . && make

$(LIB_DIR_GLFW):
	unzip $(LIB_DIR_GLFW).zip

$(LIB_GLEW): $(LIB_DIR_GLEW)
	cd $(LIB_DIR_GLEW) && make glew.lib.static

$(LIB_DIR_GLEW):
	unzip $(LIB_DIR_GLEW).zip


$(LIB_FT):
	@cd $(LIB_PATH_FT) && make

.PHONY: clean
clean:
	@cd $(LIB_PATH_FT) && make clean
	@rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@cd $(LIB_PATH_FT) && make fclean
	@rm -rf $(LIBS)
	@rm -rf $(NAME)

.PHONY: re
re: fclean all
