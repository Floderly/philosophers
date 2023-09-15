# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fderly <fderly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/09/07 19:45:39 by fderly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philosophers

SRCS =	main.c \
		ft_atoi.c \
		time.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

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
