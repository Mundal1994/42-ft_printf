# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molesen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 11:33:19 by molesen           #+#    #+#              #
#    Updated: 2022/02/09 12:21:28 by molesen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc -Wall -Wextra -Werror -I ./libft

SRC = ft_printf.c
SRC += flags.c
SRC += specifier.c
SRC += char_calc.c
SRC += int_calc.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME):
	$(CC) -c -I ./includes $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
