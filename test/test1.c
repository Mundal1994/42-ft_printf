# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>

# define RESET	"\033[0m"
# define BOLD	"\033[1m"
# define RED		"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE	"\033[34m"
# define PURPLE		"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define UNCOLOR	"\033[39m"

void	print_result(int result)
{
	if (result == 1)
		printf(CYAN"result...%d\n"UNCOLOR, result);
	else if (result == -1)
		printf(RED"result...%d\n"UNCOLOR, result);
	else
		printf(CYAN"result...%d\n"UNCOLOR, result);
}

void	print_OK(int result)
{
	if (result != 0)
		printf(RED"				KO!\n\n"UNCOLOR);
	else
		printf(GREEN"				OK!\n\n"UNCOLOR);
}

static void	compare_char(char c)
{
	int orig;

	printf("[%c]: ", c);
	printf("expected [%c] : ", c);
	orig = printf("[%c]\n", c);
	print_result(orig);
}

static void	compare_string(char *str)
{
	int orig;

	printf("[%s]: ", str);
	printf("expected [%s] : ", str);
	orig = printf("[%s]\n", str);
	print_result(orig);
}

static void	c(void)
{
	int orig;

	// CHAR
	char c = 'H';

	printf(PURPLE"\nCHAR TEST\n"UNCOLOR);
	compare_char(c);

	c = ' ';
	compare_char(c);

	c = '_';
	compare_char(c);

	c = '8';
	compare_char(c);

	c = 'm';
	compare_char(c);
}

static void	s(void)
{
	int orig;

	// STRING
	char *str = "hello";

	printf(PURPLE"\nSTRING TEST\n"UNCOLOR);
	compare_string(str);

	str = "hi my name is james";
	compare_string(str);

	str = "this is a very very very very very long string -!";
	compare_string(str);

	str = " ";
	compare_string(str);

	str = "123456789";
	compare_string(str);
}

static void	p(void)
{
	int orig;
	// POINTER
	int intnbr = 25;
	int *pnt;

	pnt = &intnbr;
	printf(PURPLE"\nPOINTER TEST\n"UNCOLOR);
	printf("[%p]: ", pnt);
	orig = printf("[%p]\n", pnt);
	print_result(orig);
}

int main(void)
{
	printf(PURPLE"char test\n"UNCOLOR);
	c();

	printf(PURPLE"\n-------\n\n"UNCOLOR);
	printf(PURPLE"string test\n"UNCOLOR);
	s();

	printf(PURPLE"\n-------\n\n"UNCOLOR);
	printf(PURPLE"pointer test\n"UNCOLOR);
	p();

	return (0);
}
