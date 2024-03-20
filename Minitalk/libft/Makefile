# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 17:13:14 by hauerbac          #+#    #+#              #
#    Updated: 2024/03/20 16:43:49 by hauerbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
DEPSFLAG = -MMD

DEBUG := 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

SRCS =  sources/strings/ft_strlen.c \
		sources/memory/ft_memset.c \
		sources/memory/ft_bzero.c \
		sources/strings/ft_strlcpy.c \
		sources/conversion/ft_spaces_truncating.c \
		sources/conversion/ft_atoi.c \
		sources/conversion/ft_itoa.c \
		sources/output/ft_putchar_fd.c \
		sources/output/ft_putstr_fd.c \
		sources/output/ft_putendl_fd.c \
		sources/output/ft_putnbr_fd.c \
		sources/conversion/ft_strtol_2.c \
		sources/conversion/ft_strtol.c

HEADERS =	includes/libft.h

OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

NAME = libft.a

all : ${NAME}

clean:
	rm -f ${OBJS}
	rm -f ${DEPS}

fclean: clean
	rm -f ${NAME}
	rm -f a.out

re: fclean all

-include ${DEPS}

%.o : %.c ${HEADERS} Makefile
	cc ${CFLAGS} ${DEPSFLAG} -I./includes -c $< -o $@

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}

