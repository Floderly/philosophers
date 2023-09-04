# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fderly <fderly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/08/27 02:51:54 by fderly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philosophers

SRCS =	main.c \
		ft_atoi.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lreadline -lhistory

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
