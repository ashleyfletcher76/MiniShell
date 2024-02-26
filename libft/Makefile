# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 12:11:50 by muhakose          #+#    #+#              #
#    Updated: 2024/02/26 12:31:42 by muhakose         ###   ########.fr        #
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
COLOR_END = \033[0m

CFLAGS	= -Wall -Wextra -Werror
RM = rm -f
CC = cc

NAME	= libft.a

SOURCES =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putstr_fd.c ft_putnbr_fd.c ft_split.c ft_strcat.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
			ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c \
			ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcpy.c get_next_line.c \
			ft_printf.c ft_putchar_fd_print.c ft_putnbr_fd_print.c ft_putstr_fd_print.c ft_unsignednbr_fd.c hexatransformlower.c \
			hexatransformupper.c ft_strlen_print.c 	ft_pointerprint.c ft_strcmp.c\
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c ft_lstiter.c\

OBJECTS	= ${SOURCES:.c=.o}

%.o : %.c
	$(CC) ${CFLAGS} -c $< -o $@

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}
	echo "$(COLOUR_YELLOW)Libft compiled successfully!$(COLOUR_END)"

all: ${NAME}

clean:
	${RM} ${OBJECTS}


fclean: clean
	${RM} ${NAME}
	echo "$(COLOUR_YELLOW)$(COLOUR_UNDERLINE)Libft cleaned successfully!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re bonus
