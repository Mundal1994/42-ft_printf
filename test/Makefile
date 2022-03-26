NAME = t1.out
NAME += t2.out
NAME += t3.out
NAME += t4.out
NAME += t5.out
NAME += t6.out
NAME += b.out

DEL = *.o
DEL += ./*.o
DEL += $(SL)*.o

SL = ../
CL = clang
CC = -g -Wall -Wextra -Werror
LIB = -I $(SL)libft
LIBPRINT = $(SL)$(SL)ft_printf/libftprintf.a
MAKELIB = make -C $(SL)libft/ fclean && make -C $(SL)libft/
MAKEPRINT = make -C $(SL)$(SL)ft_printf/ fclean && make -C $(SL)$(SL)ft_printf/

lib:
	$(MAKELIB)

t1:
	$(MAKEPRINT)
	$(CL) $(CC) $(LIB) -o test1.o -c -x c test1.test
	$(CL) -o t1.out test1.o $(LIBPRINT)

t2:
	$(MAKEPRINT)
	$(CL) $(CC) $(LIB) -o test2.o -c -x c test2.test
	$(CL) -o t2.out test2.o $(LIBPRINT)

t3:
	$(MAKEPRINT)
	$(CL) $(CC) $(LIB) -o test3.o -c -x c test3.test
	$(CL) -o t3.out test3.o $(LIBPRINT)

t4:
	$(MAKEPRINT)
	$(CL) $(CC) $(LIB) -o test4.o -c -x c test4.test
	$(CL) -o t4.out test4.o $(LIBPRINT)

t5:
	$(MAKEPRINT)
	$(CL) $(CC) $(LIB) -o test5.o -c -x c test5.test
	$(CL) -o t5.out test5.o $(LIBPRINT)

clean:
	/bin/rm -f $(DEL)

fclean: clean
	/bin/rm -f $(NAME)

al: t1 t2 t3 t4 t5 clean

all: lib t1 t2 t3 t4 t5 clean

runall:
	./t1.out
	./t2.out
	./t3.out
	./t4.out
	./t5.out

re: fclean all
