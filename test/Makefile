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
LIBFT = -I $(SL)libft -L $(SL)libft/ -lft
MAKELIB = make -C $(SL)libft/ fclean && make -C $(SL)libft/

COMP1 = $(CL) $(CC) $(LIB) -o $(SL)ft_printf.o -c $(SL)ft_printf.c
COMP2 = $(CL) $(CC) $(LIB) -o $(SL)flags.o -c $(SL)flags.c
COMP3 = $(CL) $(CC) $(LIB) -o $(SL)specifier.o -c $(SL)specifier.c

OBJ = $(SL)ft_printf.o
OBJ += $(SL)flags.o
OBJ += $(SL)specifier.o

lib:
	$(MAKELIB)

t1:
	$(COMP1)
	$(COMP2)
	$(COMP3)
	$(CL) $(CC) $(LIB) -o test1.o -c -x c test1.test
	$(CL) -o t1.out test1.o $(OBJ) $(LIBFT)

t2:
	$(COMP1)
	$(COMP2)
	$(COMP3)
	$(CL) $(CC) $(LIB) -o test2.o -c -x c test2.test
	$(CL) -o t2.out test2.o $(OBJ) $(LIBFT)

t3:
	$(COMP1)
	$(COMP2)
	$(COMP3)
	$(CL) $(CC) $(LIB) -o test3.o -c -x c test3.test
	$(CL) -o t3.out test3.o $(OBJ) $(LIBFT)

t4:
	$(COMP1)
	$(COMP2)
	$(COMP3)
	$(CL) $(CC) $(LIB) -o test4.o -c -x c test4.test
	$(CL) -o t4.out test4.o $(OBJ) $(LIBFT)

t5:
	$(COMP1)
	$(COMP2)
	$(COMP3)
	$(CL) $(CC) $(LIB) -o test5.o -c -x c test5.test
	$(CL) -o t5.out test5.o $(OBJ) $(LIBFT)

t6:
	$(COMP1)
	$(COMP2)
	$(COMP3)
	$(CL) $(CC) $(LIB) -o test6.o -c -x c test6.test
	$(CL) -o t6.out test6.o $(OBJ) $(LIBFT)

b:
	$(COMP1)
	$(COMP2)
	$(COMP3)
	$(CL) $(CC) $(LIB) -o bonus.o -c -x c bonus.test
	$(CL) -o b.out bonus.o $(OBJ) $(LIBFT)

clean:
	/bin/rm -f $(DEL)

fclean: clean
	/bin/rm -f $(NAME)

al: t1 t2 t3 t4 t5 t6 b clean

all: lib t1 t2 t3 t4 t5 t6 b clean

runall:
	./t1.out
	./t2.out
	./t3.out
	./t4.out
	./t5.out
	./t6.out

re: fclean all
