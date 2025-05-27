# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cguinot <cguinot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 11:03:46 by ebansse           #+#    #+#              #
#    Updated: 2025/05/26 17:28:33 by cguinot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = #-Wall -Wextra -Werror
INCLUDES = -I ./libft
LIB = ./libft/libft.a -lreadline
SRCS = main.c lexer.c utils.c parser.c
SRCS_ENV = env/env_init.c env/env_utils.c
SRCS_BUILTINS = builtins/ft_env.c
OBJS = $(SRCS:.c=.o) $(SRCS_ENV:.c=.o) $(SRCS_BUILTINS:.c=.o)
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