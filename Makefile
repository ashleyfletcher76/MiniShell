# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 13:16:16 by muhakose          #+#    #+#              #
#    Updated: 2024/02/26 12:24:30 by asfletch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOUR_DEFAULT = \033[0m
COLOUR_BLACK = \033[0;30m
COLOUR_RED = \033[0;31m
COLOUR_GREEN = \033[0;32m
COLOUR_YELLOW = \033[0;33m
COLOUR_BLUE = \033[0;34m
COLOUR_MAGENTA = \033[0;35m
COLOUR_CYAN = \033[0;36m
COLOUR_WHITE = \033[0;37m
COLOUR_BOLD = \033[1m
COLOUR_UNDERLINE = \033[4m

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./include/


OBJ_DIR = obj
OBJ = $(OBJ_DIR)/main.o \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/utils/*.c)) \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/parsing/*.c)) \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/builtins/*.c)) \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/execution/*.c))

NAME = minishell

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME) -lreadline
	echo "$(COLOUR_MAGENTA)Minishell compiled successfully!$(COLOUR_END)"

$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

all : $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	echo "$(COLOUR_MAGENTA)$(COLOUR_UNDERLINE)Minishell cleaned successfully!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
