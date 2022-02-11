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

static void	compare_results_f(float number)
{
	int orig;

	printf("Input: [%f]\n", number);
	printf("expected [%f] : ", number);
	orig = printf("[%f]\n", number);
	print_result(orig);
}

static void	compare_results_f_l(double number)
{
	int orig;

	printf("Input: [%lf]\n", number);
	printf("expected [%lf] : ", number);
	orig = printf("[%lf]\n", number);
	print_result(orig);
}

static void	compare_results_f_L(long double number)
{
	int orig;

	printf("Input: [%Lf]\n", number);
	printf("expected [%Lf] : ", number);
	orig = printf("[%Lf]\n", number);
	print_result(orig);
}

static void	f(void)
{
	// FLOAT
	float flo = 25.02;

	printf(PURPLE"\nFLOAT TEST\n"UNCOLOR);
	compare_results_f(flo);

	flo = 25.0250509999;
	compare_results_f(flo);

	flo = 25.0;
	compare_results_f(flo);

	flo = -25.02505;
	compare_results_f(flo);

	flo = 0;
	compare_results_f(flo);
	
	printf(PURPLE"\nl TEST\n"UNCOLOR);
	printf("l modifier: ignored does same as without it. takes in double\n");
	double doub = 25.20;
	compare_results_f_l(doub);

	doub = 12322;
	compare_results_f_l(doub);
	
	printf(PURPLE"\nL TEST\n"UNCOLOR);
	printf("L modifier: converts long double into int or unsigned int and the L makes sure it changes back to orig\n");
	long double ldoub = 25.205;
	compare_results_f_L(ldoub);

	ldoub = 250520;
	compare_results_f_L(ldoub);

/*
	printf("%f: ", 1234567.89);
	orig = printf("%'.2f\n", 1234567.89);
	print_result(orig);
	printf("%f: ", 1234567.8908);
	orig = printf("%'.2f\n", 1234567.8908);
	print_result(orig);
	printf("%f: ", 1234567.8);
	orig = printf("%'.2f\n", 1234567.8);
	print_result(orig);*/
	//mine = ft_printf("%d", number);
	//printf("Expected: [%d]	output: [%s]\n", , "5");
	//print_OK(strcmp(printf("%d", number), "5"));
}

int main(int argc, char **argv)
{
	printf(PURPLE"f test\n"UNCOLOR);
	f();
}
