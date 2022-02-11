# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

static void	compare_results_d(int number, char c)
{
	int orig;

	if (c == 'd')
	{
		printf("expected [%d] : ", number);
		orig = printf("[%d]\n", number);
		print_result(orig);
	}
	else if (c == 'i')
	{
		printf("expected [%i] : ", number);
		orig = printf("[%i]\n", number);
		print_result(orig);
	}
	else if (c == 'o')
	{
		printf("expected [%o] : ", number);
		orig = printf("[%o]\n", number);
		print_result(orig);
	}
	else if (c == 'u')
	{
		printf("expected [%u] : ", number);
		orig = printf("[%u]\n", number);
		print_result(orig);
	}
	else if (c == 'x')
	{
		printf("expected [%x] : ", number);
		orig = printf("[%x]\n", number);
		print_result(orig);
	}
	else if (c == 'X')
	{
		printf("expected [%X] : ", number);
		orig = printf("[%X]\n", number);
		print_result(orig);
	}
}

static void	compare_results_d_hh(signed char number, char c)
{
	int orig;

	if (c == 'd')
	{
		printf("expected [%hhd] : ", number);
		orig = printf("[%hhd]\n", number);
		print_result(orig);
	}
	else if (c == 'i')
	{
		printf("expected [%hhi] : ", number);
		orig = printf("[%hhi]\n", number);
		print_result(orig);
	}
	else if (c == 'o')
	{
		printf("expected [%hho] : ", number);
		orig = printf("[%hho]\n", number);
		print_result(orig);
	}
	else if (c == 'u')
	{
		printf("expected [%hhu] : ", number);
		orig = printf("[%hhu]\n", number);
		print_result(orig);
	}
	else if (c == 'x')
	{
		printf("expected [%hhx] : ", number);
		orig = printf("[%hhx]\n", number);
		print_result(orig);
	}
	else if (c == 'X')
	{
		printf("expected [%hhX] : ", number);
		orig = printf("[%hhX]\n", number);
		print_result(orig);
	}
}

static void	compare_results_d_h(short number, char c)
{
	int orig;

	if (c == 'd')
	{
		printf("expected [%hd] : ", number);
		orig = printf("[%hd]\n", number);
		print_result(orig);
	}
	else if (c == 'i')
	{
		printf("expected [%hi] : ", number);
		orig = printf("[%hi]\n", number);
		print_result(orig);
	}
	else if (c == 'o')
	{
		printf("expected [%ho] : ", number);
		orig = printf("[%ho]\n", number);
		print_result(orig);
	}
	else if (c == 'u')
	{
		printf("expected [%hu] : ", number);
		orig = printf("[%hu]\n", number);
		print_result(orig);
	}
	else if (c == 'x')
	{
		printf("expected [%hx] : ", number);
		orig = printf("[%hx]\n", number);
		print_result(orig);
	}
	else if (c == 'X')
	{
		printf("expected [%hX] : ", number);
		orig = printf("[%hX]\n", number);
		print_result(orig);
	}
}

static void	compare_results_d_l(long number, char c)
{
	int orig;

	if (c == 'd')
	{
		printf("expected [%ld] : ", number);
		orig = printf("[%ld]\n", number);
		print_result(orig);
	}
	else if (c == 'i')
	{
		printf("expected [%li] : ", number);
		orig = printf("[%li]\n", number);
		print_result(orig);
	}
	else if (c == 'o')
	{
		printf("expected [%lo] : ", number);
		orig = printf("[%lo]\n", number);
		print_result(orig);
	}
	else if (c == 'u')
	{
		printf("expected [%lu] : ", number);
		orig = printf("[%lu]\n", number);
		print_result(orig);
	}
	else if (c == 'x')
	{
		printf("expected [%lx] : ", number);
		orig = printf("[%lx]\n", number);
		print_result(orig);
	}
	else if (c == 'X')
	{
		printf("expected [%lX] : ", number);
		orig = printf("[%lX]\n", number);
		print_result(orig);
	}
}

static void	compare_results_d_ll(long long number, char c)
{
	int orig;

	if (c == 'd')
	{
		printf("expected [%lld] : ", number);
		orig = printf("[%lld]\n", number);
		print_result(orig);
	}
	else if (c == 'i')
	{
		printf("expected [%lli] : ", number);
		orig = printf("[%lli]\n", number);
		print_result(orig);
	}
	else if (c == 'o')
	{
		printf("expected [%llo] : ", number);
		orig = printf("[%llo]\n", number);
		print_result(orig);
	}
	else if (c == 'u')
	{
		printf("expected [%llu] : ", number);
		orig = printf("[%llu]\n", number);
		print_result(orig);
	}
	else if (c == 'x')
	{
		printf("expected [%llx] : ", number);
		orig = printf("[%llx]\n", number);
		print_result(orig);
	}
	else if (c == 'X')
	{
		printf("expected [%llX] : ", number);
		orig = printf("[%llX]\n", number);
		print_result(orig);
	}
}

static void	d(void)
{
	int	orig;
	// DECIMAL INTEGER (ASSUMES BASE 10)
	//assumes integer is a signed decimal number
	int	number = 5;

	printf(PURPLE"\nDECIMAL INTEGER (ASSUMES BASE 10) TEST\n"UNCOLOR);
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'd');

	number = 2147483647;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'd');

	number = -2147483648;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'd');

	number = -1234;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'd');

	number = 1234;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'd');

	number = -0;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'd');

	// difference between %d and %i
	printf(PURPLE"\ndifference between %%d and %%i TEST\n"UNCOLOR);
	number = 012;
	printf("Input: [012]\n");
	compare_results_d(number, 'd');

	number = 033;
	printf("Input: [033]\n");
	compare_results_d(number, 'd');

	// with flags hh
	unsigned char	c = '5';
	printf(PURPLE"\nhh TEST\n"UNCOLOR);
	printf("hh modifier: converts signed / usigned char into int or unsigned int and the hh makes sure it changes back to char\n");
	printf("[%hhd]: ", c);
	orig = printf("[%hhd]\n", c);
	print_result(orig);

	c = 'M';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'd');

	c = 'a';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'd');

	c = 'z';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'd');

	c = ' ';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'd');

	// with flags h
	short	shor = 5;
	printf(PURPLE"\nh TEST\n"UNCOLOR);
	printf("h modifier: converts short into int or unsigned int and the h makes sure it changes back to short int or unsigned short int\n");
	printf("Input: [%c]\n", shor);
	compare_results_d_h(shor, 'd');

	shor = -32768;
	printf("Input: [%c]\n", shor);
	compare_results_d_h(shor, 'd');

	shor = 32767;
	printf("Input: [%c]\n", shor);
	compare_results_d_h(shor, 'd');

	shor = 0;
	printf("Input: [%c]\n", shor);
	compare_results_d_h(shor, 'd');

	shor = 1234;
	printf("Input: [%c]\n", shor);
	compare_results_d_h(shor, 'd');

	// with flags l
	long	lon = 5;
	printf(PURPLE"\nl TEST\n"UNCOLOR);
	printf("l modifier: converts long int into int or unsigned int and the l makes sure it changes back to long int or unsigned long int\n");
	printf("[%lu]: ", lon);
	compare_results_d_l(lon, 'd');

	lon = -2147483648;
	printf("[%lu]: ", lon);
	compare_results_d_l(lon, 'd');

	lon = 2147483647;
	printf("[%lu]: ", lon);
	compare_results_d_l(lon, 'd');

	lon = 0;
	printf("[%lu]: ", lon);
	compare_results_d_l(lon, 'd');

	lon = 1234;
	printf("[%lu]: ", lon);
	compare_results_d_l(lon, 'd');
	//shouldn't work to put in long max value or min value

	// with flags ll
	long long int	longlong = 5;
	printf(PURPLE"\nll TEST\n"UNCOLOR);
	printf("ll modifier: converts long long int into int or unsigned int and the ll makes sure it changes back to long int or unsigned long long int\n");
	printf("[%llu]: ", longlong);
	compare_results_d_ll(longlong, 'd');

	longlong = -2147483648;
	printf("[%llu]: ", longlong);
	compare_results_d_ll(longlong, 'd');

	longlong = 2147483647;
	printf("[%llu]: ", longlong);
	compare_results_d_ll(longlong, 'd');

	longlong = 0;
	printf("[%llu]: ", longlong);
	compare_results_d_ll(longlong, 'd');

	longlong = 1234;
	printf("[%llu]: ", longlong);
	compare_results_d_ll(longlong, 'd');

	//mine = ft_printf("%d", number);
	//printf("Expected: [%d]	output: [%s]\n", , "5");
	//print_OK(strcmp(printf("%d", number), "5"));
}

static void	i(void)
{
	// DEMICAL INTEGER (DETECTS THE BASE AUTOMATICALLY)
	// defaults to decimal but also reads hexadecimal (if start is 0x) or octal (if start with 0)
	int	orig;
	int	number = 5;

	printf(PURPLE"\nDEMICAL INTEGER (DETECTS THE BASE AUTOMATICALLY) TEST\n"UNCOLOR);
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'i');

	number = 2147483647;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'i');

	number = -2147483648;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'i');

	number = -1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'i');

	number = 1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'i');

	number = -0;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'i');

	// difference between %d and %i
	printf(PURPLE"\ndifference between %%d and %%i TEST\n"UNCOLOR);
	number = 012;
	printf("Input: [012]\n");
	compare_results_d(number, 'i');

	number = 033;
	printf("Input: [033]\n");
	compare_results_d(number, 'i');

	number = 0x12;
	printf("Input: [0x12]\n");
	compare_results_d(number, 'i');

	// with flags hh
	unsigned char	c = '5';
	printf(PURPLE"\nhh TEST\n"UNCOLOR);
	printf("hh modifier: converts signed / usigned char into int or unsigned int and the hh makes sure it changes back to char\n");
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'i');

	c = 'M';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'i');

	c = 'a';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'i');

	c = 'z';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'i');

	c = ' ';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'i');

	// with flags h
	short int	shor = 5;
	printf(PURPLE"\nh TEST\n"UNCOLOR);
	printf("h modifier: converts short into int or unsigned int and the h makes sure it changes back to short int or unsigned short int\n");
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'i');

	shor = -32768;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'i');

	shor = 32767;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'i');

	shor = 0;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'i');

	shor = 1234;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'i');

	// with flags l
	long int	lon = 5;
	printf(PURPLE"\nl TEST\n"UNCOLOR);
	printf("l modifier: converts long int into int or unsigned int and the l makes sure it changes back to long int or unsigned long int\n");
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'i');

	lon = -2147483648;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'i');

	lon = 2147483647;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'i');

	lon = 0;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'i');

	lon = 1234;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'i');
	//shouldn't work to put in long max value or min value

	// with flags ll
	long long int	longlong = 5;
	printf(PURPLE"\nll TEST\n"UNCOLOR);
	printf("ll modifier: converts long long int into int or unsigned int and the ll makes sure it changes back to long int or unsigned long long int\n");
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'i');

	longlong = -2147483648;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'i');

	longlong = 2147483647;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'i');

	longlong = 0;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'i');

	longlong = 1234;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'i');
}

static void	o(void)
{
	// OCTAL (base 8) integer
	int	orig;
	int	number = 150;

	printf(PURPLE"\nOCTAL (base 8) INTEGER TEST\n"UNCOLOR);
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'o');

	number = 31;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'o');

	number = 0;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'o');

	number = -1234;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'o');

	number = 1234;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'o');

	number = 15;
	printf("Input: [%d]\n", number);
	compare_results_d(number, 'o');

	// with flags hh
	unsigned char	c = '5';
	printf(PURPLE"\nhh TEST\n"UNCOLOR);
	printf("hh modifier: converts signed / usigned char into int or unsigned int and the hh makes sure it changes back to char\n");
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'o');

	c = 'M';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'o');

	c = 'a';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'o');

	c = 'z';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'o');

	c = ' ';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'o');

	// with flags h
	unsigned short	shor = 5;
	printf(PURPLE"\nh TEST\n"UNCOLOR);
	printf("h modifier: converts short into int or unsigned int and the h makes sure it changes back to short int or unsigned short int\n");
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'o');

	shor = -32768;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'o');

	shor = 32767;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'o');

	shor = 0;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'o');

	shor = 1234;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'o');

	// with flags l
	unsigned long	lon = 5;
	printf(PURPLE"\nl TEST\n"UNCOLOR);
	printf("l modifier: converts long int into int or unsigned int and the l makes sure it changes back to long int or unsigned long int\n");
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'o');

	lon = -2147483648;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'o');

	lon = 2147483647;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'o');

	lon = 0;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'o');

	lon = 1234;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'o');
	//shouldn't work to put in long max value or min value

	// with flags ll
	unsigned long long	longlong = 5;
	printf(PURPLE"\nll TEST\n"UNCOLOR);
	printf("ll modifier: converts unsigned long long int into int or unsigned int and the ll makes sure it changes back to long int or unsigned unsigned long long int\n");
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'o');

	longlong = -2147483648;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'o');

	longlong = 2147483647;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'o');

	longlong = 0;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'o');

	longlong = 1234;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'o');
}

static void	u(void)
{
	// INT UNSIGNED DECIMAL (non negative numbers)
	int	orig;
	unsigned int	number = 5;

	printf(PURPLE"\nINT UNSIGNED DECIMAL (non negative numbers) TEST\n"UNCOLOR);
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'u');

	number = 2147483647;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'u');

	number = -2147483648;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'u');

	number = -1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'u');

	number = 1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'u');

	number = -0;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'u');

	// with flags hh
	unsigned char	c = '5';
	printf(PURPLE"\nhh TEST\n"UNCOLOR);
	printf("hh modifier: converts signed / usigned char into int or unsigned int and the hh makes sure it changes back to char\n");
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'u');

	c = 'M';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'u');

	c = 'a';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'u');

	c = 'z';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'u');

	c = ' ';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'u');

	// with flags h
	short int	shor = 5;
	printf(PURPLE"\nh TEST\n"UNCOLOR);
	printf("h modifier: converts short into int or unsigned int and the h makes sure it changes back to short int or unsigned short int\n");
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'u');

	shor = -32768;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'u');

	shor = 32767;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'u');

	shor = 0;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'u');

	shor = 1234;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'u');

	// with flags l
	long int	lon = 5;
	printf(PURPLE"\nl TEST\n"UNCOLOR);
	printf("l modifier: converts long int into int or unsigned int and the l makes sure it changes back to long int or unsigned long int\n");
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'u');

	lon = -2147483648;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'u');

	lon = 2147483647;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'u');

	lon = 0;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'u');

	lon = 1234;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'u');
	//shouldn't work to put in long max value or min value

	// with flags ll
	long long int	longlong = 5;
	printf(PURPLE"\nll TEST\n"UNCOLOR);
	printf("ll modifier: converts long long int into int or unsigned int and the ll makes sure it changes back to long int or unsigned long long int\n");
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'u');

	longlong = -2147483648;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'u');

	longlong = 2147483647;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'u');

	longlong = 0;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'u');

	longlong = 1234;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'u');
}


static void	x(void)
{
	// HEXADECIMAL (base 16) INTEGER (small characters)
	int	orig;
	int	number = 0x5;

	printf(PURPLE"\nHEXADECIMAL (base 16) INTEGER (small characters) TEST\n"UNCOLOR);
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'x');

	number = 0x7fffffff;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'x');

	number = -0x7fffffff;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'x');

	number = -0x1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'x');

	number = 0x1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'x');

	number = -0x0;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'x');

	// with flags hh
	unsigned char	c = '5';
	printf(PURPLE"\nhh TEST\n"UNCOLOR);
	printf("hh modifier: converts signed / usigned char into int or unsigned int and the hh makes sure it changes back to char\n");
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'x');

	c = 'M';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'x');

	c = 'a';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'x');

	c = 'z';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'x');

	c = ' ';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'x');

	// with flags h
	short int	shor = 5;
	printf(PURPLE"\nh TEST\n"UNCOLOR);
	printf("h modifier: converts short into int or unsigned int and the h makes sure it changes back to short int or unsigned short int\n");
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'x');

	shor = -32768;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'x');

	shor = 32767;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'x');

	shor = 0;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'x');

	shor = 1234;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'x');

	// with flags l
	long int	lon = 5;
	printf(PURPLE"\nl TEST\n"UNCOLOR);
	printf("l modifier: converts long int into int or unsigned int and the l makes sure it changes back to long int or unsigned long int\n");
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'x');

	lon = -2147483648;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'x');

	lon = 2147483647;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'x');

	lon = 0;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'x');

	lon = 1234;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'x');
	//shouldn't work to put in long max value or min value

	// with flags ll
	long long int	longlong = 5;
	printf(PURPLE"\nll TEST\n"UNCOLOR);
	printf("ll modifier: converts long long int into int or unsigned int and the ll makes sure it changes back to long int or unsigned long long int\n");
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'x');

	longlong = -2147483648;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'x');

	longlong = 2147483647;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'x');

	longlong = 0;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'x');

	longlong = 1234;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'x');
}

static void	X(void)
{
	// HEXADECIMAL (base 16) INTEGER (big characters)
	int	number = 0x5;

	printf(PURPLE"\nHEXADECIMAL (base 16) INTEGER (small characters) TEST\n"UNCOLOR);
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'X');

	number = 0x7FFFFFFF;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'X');

	number = -0x7FFFFFFF;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'X');

	number = -0x1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'X');

	number = 0x1234;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'X');

	number = -0x0;
	printf("Input: [%i]\n", number);
	compare_results_d(number, 'X');

	// with flags hh
	unsigned char	c = '5';
	printf(PURPLE"\nhh TEST\n"UNCOLOR);
	printf("hh modifier: converts signed / usigned char into int or unsigned int and the hh makes sure it changes back to char\n");
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'X');

	c = 'M';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'X');

	c = 'a';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'X');

	c = 'z';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'X');

	c = ' ';
	printf("Input: [%c]\n", c);
	compare_results_d_hh(c, 'X');

	// with flags h
	short int	shor = 5;
	printf(PURPLE"\nh TEST\n"UNCOLOR);
	printf("h modifier: converts short into int or unsigned int and the h makes sure it changes back to short int or unsigned short int\n");
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'X');

	shor = -32768;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'X');

	shor = 32767;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'X');

	shor = 0;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'X');

	shor = 1234;
	printf("Input: [%d]\n", shor);
	compare_results_d_h(shor, 'X');

	// with flags l
	long int	lon = 5;
	printf(PURPLE"\nl TEST\n"UNCOLOR);
	printf("l modifier: converts long int into int or unsigned int and the l makes sure it changes back to long int or unsigned long int\n");
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'X');

	lon = -2147483648;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'X');

	lon = 2147483647;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'X');

	lon = 0;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'X');

	lon = 1234;
	printf("Input: [%lu]\n", lon);
	compare_results_d_l(lon, 'X');
	//shouldn't work to put in long max value or min value

	// with flags ll
	long long int	longlong = 5;
	printf(PURPLE"\nll TEST\n"UNCOLOR);
	printf("ll modifier: converts long long int into int or unsigned int and the ll makes sure it changes back to long int or unsigned long long int\n");
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'X');

	longlong = -2147483648;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'X');

	longlong = 2147483647;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'X');

	longlong = 0;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'X');

	longlong = 1234;
	printf("Input: [%llu]\n", longlong);
	compare_results_d_ll(longlong, 'X');
}

int main(void)
{
	printf(PURPLE"decimal integer (assume base 10) test\n"UNCOLOR);
	d();

	printf(PURPLE"\n-------\n\n"UNCOLOR);
	printf(PURPLE"decimal integer (detects base automatically) test\n"UNCOLOR);
	i();

	printf(PURPLE"\n-------\n\n"UNCOLOR);
	printf(PURPLE"octal (base 8) integer test\n"UNCOLOR);
	o();

	printf(PURPLE"\n-------\n\n"UNCOLOR);
	printf(PURPLE"int unsigned decimal test\n"UNCOLOR);
	u();

	printf(PURPLE"\n-------\n\n"UNCOLOR);
	printf(PURPLE"hexadecimal (base 16) integer (small char) test\n"UNCOLOR);
	x();

	printf(PURPLE"\n-------\n\n"UNCOLOR);
	printf(PURPLE"hexadecimal (base 16) integer (big char) test\n"UNCOLOR);
	X();
}
