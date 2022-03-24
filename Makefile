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
SRC += width_calc.c
SRC += str_print.c
SRC += digit_calc.c
SRC += digit_print.c
SRC += ox_print.c
SRC += f_print.c
SRC += ftoa.c
SRC += bonus.c
SRC += sign_print.c

OBJ = $(SRC:.c=.o)

MAKELIB = make -C libft/ fclean && make -C libft/

all: $(NAME)
$(NAME):
	$(MAKELIB)
	$(CC) -c -I ./includes $(SRC)
	ar rc $(NAME) $(OBJ) libft/*.o
	ranlib $(NAME)

clean:
	/bin/rm -f *.o
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
