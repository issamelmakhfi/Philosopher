# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 08:21:12 by issam             #+#    #+#              #
#    Updated: 2022/08/07 16:10:18 by ielmakhf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main_programe.c philo_utils.c philo_functions.c philo_utils2.c

OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all