# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 18:06:08 by aouchaad          #+#    #+#              #
#    Updated: 2023/04/09 22:51:59 by aouchaad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	dead_philo.c \
			ft_atoi.c \
			main_utils.c \
			routine.c \
			threads_and_mutexs.c \
			args_check.c

OBJS	=	${SRCS:.c=.o}

NAME	=	philo

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

all : $(NAME)

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS} philo.c philo.h
	${CC} ${CFLAGS} ${OBJS} philo.c -o $@

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean