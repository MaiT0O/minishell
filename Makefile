# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 11:03:46 by ebansse           #+#    #+#              #
#    Updated: 2025/05/22 16:52:33 by ebansse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = #-Wall -Wextra -Werror
INCLUDES = -I ./libft
LIB = ./libft/libft.a -lreadline
SRCS = main.c lexer.c utils.c parser.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

#colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Rules
all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) ${INCLUDES} -c $< -o $@

$(NAME): make_libs $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) ${INCLUDES} -o $(NAME)
	@echo "${CYAN}$(NAME) compiled successfully!${RESET}"

clean:
	@rm -f $(OBJS)
	@echo "${MAGENTA}${NAME} object files cleaned!${RESET}"
	make -C libft fclean

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}${NAME} binaries cleaned!${RESET}"

make_libs:
	make -C libft

re: fclean all