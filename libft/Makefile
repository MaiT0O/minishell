# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 11:18:44 by ebansse           #+#    #+#              #
#    Updated: 2024/11/07 11:18:44 by ebansse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
AR		= ar rcs
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCS    = ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c \
		ft_strlcat.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
		ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c \
		ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
		ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
		ft_putstr_fd.c  ft_substr.c  ft_strjoin.c  ft_strtrim.c  ft_itoa.c \
		ft_strmapi.c  ft_striteri.c  ft_split.c

BONUS	= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
			ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

PRINTF = printf/ft_put.c printf/ft_puthex.c printf/ft_nbr_base.c printf/ft_printf.c

GNL = gnl/get_next_line.c

CUSTOM = custom/ft_str_only_chr.c custom/ft_strcmp.c custom/ft_strncpy.c custom/ft_atoi_custom.c

OBJS    =  ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}
PRINTF_OBJS = ${PRINTF:.c=.o}
GNL_OBJS = ${GNL:.c=.o}
CUSTOM_OBJS = ${CUSTOM:.c=.o}

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

all : ${NAME}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

${NAME} : ${OBJS} ${BONUS_OBJS} ${PRINTF_OBJS} ${GNL_OBJS} ${CUSTOM_OBJS}
	@${AR} ${NAME} ${OBJS} ${BONUS_OBJS} ${PRINTF_OBJS} ${GNL_OBJS} ${CUSTOM_OBJS}
	@echo "${GREEN}Libft compiled successfully!${RESET}"

clean :
	@rm -f ${OBJS} ${BONUS_OBJS} ${PRINTF_OBJS} ${GNL_OBJS} ${CUSTOM_OBJS}
	@echo "${MAGENTA}Libft objects files cleaned!${RESET}"

fclean : clean
	@rm -f ${NAME}
	@echo "${RED}Libft binaries cleaned!${RESET}"

re : fclean all