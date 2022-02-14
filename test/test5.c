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

static void	compare_results_width(int number)
{
	int orig;

	printf("\nInput width: [%d]\n", number);
	printf("expected [%.10d] : ", number);
	orig = printf("[%.10d]\n", number);
	print_result(orig);
}

static void	compare_results_0(int number)
{
	int orig;

	printf("\nInput 0: [%d]\n", number);
	printf("expected [%010d] : ", number);
	orig = printf("[%010d]\n", number);
	print_result(orig);
}

static void	width(void)
{
	int number;

	// width
	printf(PURPLE"\nWIDTH & PRECISION TEST\n"UNCOLOR);
	number = -10;
	printf("\n[.10] pads the converted number with leading zeroes up to 10 digits\n");
	compare_results_width(number);
	printf("\n[010] pads the output with leading zeroes up to a width of 10 characters\n");
	compare_results_0(number);

	number = 10;
	compare_results_width(number);
	compare_results_0(number);

	number = 0;
	int orig;

	printf("\nInput width: [%d]\n", number);
	printf("expected [%00d] : ", number);
	orig = printf("[%00d]\n", number);
	print_result(orig);

	printf("\nInput 0: [%d]\n", number);
	printf("expected [%.0d] : ", number);
	orig = printf("[%.0d]\n", number);
	print_result(orig);

	number = 5;
	char *pointer = "little";
	printf("\nprecision: [4] and [10]\n");
	printf("Here is a number[%4d]and a[%10s]word.\n", number, pointer);
}

int main(void)
{
	printf(PURPLE"with test\n"UNCOLOR);
	width();
}
