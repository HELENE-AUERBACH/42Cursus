# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 15:26:07 by hauerbac          #+#    #+#              #
#    Updated: 2024/03/19 17:42:44 by hauerbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror 
DEPSFLAG = -MMD

DEBUG := 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

CLIENT_SRCS_DIR = client

SERVER_SRCS_DIR = server

SRCS_DIR = srcs

vpath %.c ${SRCS_DIR}

CLIENT_SRCS =	${CLIENT_SRCS_DIR}/client_minitalk.c

SERVER_SRCS =	${SERVER_SRCS_DIR}/server_minitalk.c

CLIENT_HEADERS =	includes/client/client_minitalk.h

SERVER_HEADERS =	includes/server/server_minitalk.h

BUILD_DIR = .build
CLIENT_OBJS = $(addprefix $(BUILD_DIR)/, $(CLIENT_SRCS:%.c=%.o))
CLIENT_DEPS = $(addprefix $(BUILD_DIR)/, $(CLIENT_SRCS:%.c=%.d))
SERVER_OBJS = $(addprefix $(BUILD_DIR)/, $(SERVER_SRCS:%.c=%.o))
SERVER_DEPS = $(addprefix $(BUILD_DIR)/, $(SERVER_SRCS:%.c=%.d))

LIBFT_DIR = libft

LIBFT = ${LIBFT_DIR}/libft.a

CLIENT_NAME = client

SERVER_NAME = server

all : LIBRARY BUILD ${CLIENT_NAME} ${SERVER_NAME}

LIBRARY:
	make -C ${LIBFT_DIR} all

BUILD:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${BUILD_DIR}/client
	mkdir -p ${BUILD_DIR}/server

clean:
	make -C ${LIBFT_DIR} clean
	rm -rf ${BUILD_DIR}

fclean: clean
	rm -f ${CLIENT_NAME}
	rm -f ${SERVER_NAME}
	rm -f a.out
	rm -f ${LIBFT}

re: fclean all

-include ${CLIENT_DEPS} ${SERVER_DEPS}

${BUILD_DIR}/client/%.o : client/%.c ${CLIENT_HEADERS} Makefile
	cc ${CFLAGS} ${DEPSFLAG} -I./includes/client -c $< -o $@

${BUILD_DIR}/server/%.o : server/%.c ${SERVER_HEADERS} Makefile
	cc ${CFLAGS} ${DEPSFLAG} -I./includes/server -c $< -o $@

${CLIENT_NAME}: ${CLIENT_OBJS}
	cc ${CFLAGS} ${DEPSFLAG} -o ${CLIENT_NAME} ${CLIENT_OBJS} -L${LIBFT_DIR} -lft

${SERVER_NAME}: ${SERVER_OBJS}
	cc ${CFLAGS} ${DEPSFLAG} -o ${SERVER_NAME} ${SERVER_OBJS} -L${LIBFT_DIR} -lft

.PHONY: all clean fclean re
