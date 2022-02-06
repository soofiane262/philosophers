# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 20:28:50 by sel-mars          #+#    #+#              #
#    Updated: 2022/01/31 20:28:51 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar rc

LIB		=	libphilo.a

HDFL	=	philo.h

SRCS	=	philo.c philo_00_utils.c philo_01_parse.c philo_02_threads.c

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -c $(SRCS) -I $(HDFL)
	$(AR) $(LIB) $(OBJS)
	$(CC) $(CFLAGS) main.c -L. -lphilo -o $(NAME)

clean:
	rm -f $(OBJS) $(LIB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
