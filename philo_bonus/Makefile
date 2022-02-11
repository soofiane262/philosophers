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

NAME	=	philo_bonus

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar rc

LIB		=	libphilo_bonus.a

HDFL	=	philo_bonus.h

SRCS	=	philo_bonus.c philo_00_utils_bonus.c philo_01_parse_bonus.c philo_02_create_bonus.c\
			philo_03_fork_bonus.c

OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(HDFL)
	$(AR) $(LIB) $(OBJS)
	$(CC) $(CFLAGS) main_bonus.c -L. -lphilo_bonus -o $(NAME)

clean:
	rm -f $(OBJS) $(LIB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
