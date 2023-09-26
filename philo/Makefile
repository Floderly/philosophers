# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fderly <fderly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/09/24 20:57:59 by fderly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philosophers

SRCS =	main.c \
		ft_atoi.c \
		time.c \
		check_death.c \
		thread_philo.c \
		thread_philo_2.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread #-g -O2 -pthread -fsanitize=thread

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:
		rm -f $(OBJS) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
