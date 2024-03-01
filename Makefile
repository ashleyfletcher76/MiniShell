# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 13:16:16 by muhakose          #+#    #+#              #
#    Updated: 2024/03/01 18:30:14 by muhakose         ###   ########.fr        #
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
COLOUR_END = \033[0m

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./include/ -g

#VALGRIND_ENABLED = 1

#VALGRIND_CMD = valgrind
#VALGRIND_OPTS = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes

#TARGET = minishell

#$(TARGET): $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)


#run_valgrind: $(TARGET)
#	@echo "Running $(TARGET) with Valgrind..."
#	$(VALGRIND_CMD) $(VALGRIND_OPTS) ./$(TARGET)

CFLAGS += -Wall -Wextra -Werror -I./include/ -g3 -fsanitize=address -fsanitize=undefined
LDFLAGS += -fsanitize=address -fsanitize=undefined -lreadline

OBJ_DIR = obj
OBJ = $(OBJ_DIR)/main.o \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/utils/*.c)) \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/parsing/*.c)) \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/builtins/*.c)) \
	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/execution/*.c))

NAME = minishell

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

$(NAME) : $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME) -lreadline
	echo "$(COLOUR_MAGENTA)Minishell compiled successfully!$(COLOUR_END)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/builtins
	mkdir -p $(OBJ_DIR)/execution

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

all : $(NAME)

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	echo "$(COLOUR_MAGENTA)$(COLOUR_UNDERLINE)Minishell cleaned successfully!$(COLOUR_END)"

re: fclean all


.PHONY: all clean fclean re

valgrind:
	$(MAKE) run_valgrind

# Define a target to show Valgrind error messages
.PHONY: show_errors
show_errors:
	$(VALGRIND_CMD) $(VALGRIND_OPTS) --log-file=valgrind_errors.txt ./$(TARGET)
	cat valgrind_errors.txt
	rm -f valgrind_errors.txt
