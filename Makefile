# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 18:06:08 by aouchaad          #+#    #+#              #
#    Updated: 2023/04/29 08:52:14 by aouchaad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	dead_philo.c \
			ft_atoi.c \
			main_utils.c \
			routine.c \
			threads_and_mutexs.c \
			args_check.c \
			my_usleep.c \
			take_fork.c

OBJS	=	${SRCS:.c=.o}

NAME	=	philo

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -pthread

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

re : fclean all

it : all clean