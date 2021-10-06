#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2020\05\07 14:56:02 by matrus            #+#    #+#             *#
#*   Updated: 2020\05\07 14:56:02 by matrus           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = libft.a

INCLUDES_DIR =	.
INCLUDES =		libft.h

DIR_CHAR =		char
SRC_CHAR = 		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_toupper.c ft_tolower.c ft_isspace.c

DIR_MEMORY =	memory
SRC_MEMORY =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c ft_calloc.c ft_realloc_tab.c \
				ft_free_tab.c ft_tabdup.c

DIR_OUTPUT =	output
SRC_OUTPUT =	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

DIR_STRING =	string
SRC_STRING =	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
				ft_strmapi.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_atoi.c \
				ft_strrchr.c ft_strchr.c ft_strnstr.c ft_strncmp.c ft_strdup.c

DIR_LIST =		list
SRC_LIST =		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

DIR_NUMB =		number
SRC_NUMB =		ft_ilen.c

DIR_GNL =		gnl
SRC_GNL =		get_next_line.c get_next_line_utils.c

OBJ_DIR =		obj
OBJ =	$(SRC_CHAR:%.c=$(DIR_CHAR)/%.o)	$(SRC_MEMORY:%.c=$(DIR_MEMORY)/%.o) \
		$(SRC_OUTPUT:%.c=$(DIR_OUTPUT)/%.o) $(SRC_STRING:%.c=$(DIR_STRING)/%.o) \
		$(SRC_LIST:%.c=$(DIR_LIST)/%.o) $(SRC_NUMB:%.c=$(DIR_NUMB)/%.o) \
		$(SRC_GNL:%.c=$(DIR_GNL)/%.o)

		
FLAGS = -Wall -Werror -Wextra
CC = gcc

TMP = $(OBJ:%=$(OBJ_DIR)/%)


.PHONY: all
all: $(OBJ_DIR) $(NAME)

$(NAME): $(TMP)
	ar rcs $(NAME) $?

$(TMP): $(OBJ_DIR)/%.o: %.c $(INCLUDES)	
	$(CC) $(FLAGS) -c -I$(INCLUDES_DIR) $< -o $@

$(OBJ_DIR):
	mkdir 	$@ $@/$(DIR_CHAR) $@/$(DIR_MEMORY) $@/$(DIR_LIST) $@/$(DIR_STRING) \
			$@/$(DIR_NUMB) $@/$(DIR_OUTPUT) $@/$(DIR_GNL)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
