# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 16:09:02 by hauerbac          #+#    #+#              #
#    Updated: 2024/03/24 18:14:42 by hauerbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror 
DEPSFLAG = -MMD

DEBUG := 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

SRCS_DIR = srcs

vpath %.c ${SRCS_DIR}

SRCS =	parsing_philo.c \
	utils_philo.c \
	observer_philo.c \
	actions_philo.c \
	main_philo.c

HEADERS =	includes/philo.h

BUILD_DIR = .build
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
DEPS = $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.d))

NAME = philo

all : BUILD ${NAME}

BUILD:
	mkdir -p ${BUILD_DIR}

clean:
	rm -rf ${BUILD_DIR}

fclean: clean
	rm -f ${NAME}
	rm -f a.out

re: fclean all

-include ${DEPS}

${BUILD_DIR}/%.o : %.c ${HEADERS} Makefile
	cc ${CFLAGS} ${DEPSFLAG} -I./includes -c $< -o $@

${NAME}: ${OBJS}
	cc ${CFLAGS} ${DEPSFLAG} -o ${NAME} ${OBJS}

.PHONY: all clean fclean re
