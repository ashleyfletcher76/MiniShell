# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 13:16:16 by muhakose          #+#    #+#              #
#    Updated: 2024/02/22 14:14:52 by muhakose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOUR_GREEN = \033[0;32m
COLOUR_RED = \033[0;31m
COLOUR_BLUE = \033[0;34m
COLOUR_END = \033[0m

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror


OBJ = src/main.c $(wildcard src/pipex/*.c) $(wildcard src/utils/*.c) $(wildcard src/parsing/*.c) $(wildcard src/builtins/*.c) $(wildcard src/execution/*.c)
OBJ_MINISHELL = $(OBJ:.c=.o)

NAME = minishell

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME) : $(OBJ_MINISHELL) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_MINISHELL) $(LIBFT) $(LDFLAGS) -o $(NAME) -lreadline
	$(RM) $(OBJ_MINISHELL)
	echo "$(COLOUR_GREEN)Minishell compiled successfully!$(COLOUR_END)"

$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

all : $(NAME)

clean:
	$(RM) $(OBJ_MINISHELL)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	echo "$(COLOUR_BLUE)Minishell cleaned successfully!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
