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

static void	simple(void)
{
	int orig;

	// CHAR
	char c = 'H';

	printf(PURPLE"\nCHAR TEST\n"UNCOLOR);
	printf("[%c]: ", c);
	orig = printf("[%c]\n", c);
	print_result(orig);

	c = ' ';
	printf("[%c]: ", c);
	orig = printf("[%c]\n", c);
	print_result(orig);

	c = '_';
	printf("[%c]: ", c);
	orig = printf("[%c]\n", c);
	print_result(orig);

	c = '8';
	printf("[%c]: ", c);
	orig = printf("[%c]\n", c);
	print_result(orig);

	c = 'm';
	printf("[%c]: ", c);
	orig = printf("[%c]\n", c);
	print_result(orig);

	// STRING
	char *str = "hello";

	printf(PURPLE"\nSTRING TEST\n"UNCOLOR);
	printf("[%s]: ", str);
	orig = printf("[%s]\n", str);
	print_result(orig);

	str = "hi my name is james";
	printf("[%s]: ", str);
	orig = printf("[%s]\n", str);
	print_result(orig);

	str = "this is a very very very very very long string -!";
	printf("[%s]: ", str);
	orig = printf("[%s]\n", str);
	print_result(orig);

	str = " ";
	printf("[%s]: ", str);
	orig = printf("[%s]\n", str);
	print_result(orig);

	str = "123456789";
	printf("[%s]: ", str);
	orig = printf("[%s]\n", str);
	print_result(orig);

	// INTEGER
	int	number = 5;

	printf(PURPLE"\nINT TEST\n"UNCOLOR);
	printf("[%d]: ", number);
	orig = printf("[%d]\n", number);
	print_result(orig);

	number = 2147483647;
	printf("[%d]: ", number);
	orig = printf("[%d]\n", number);
	print_result(orig);

	number = -2147483648;
	printf("[%d]: ", number);
	orig = printf("[%d]\n", number);
	print_result(orig);

	number = -1234;
	printf("[%d]: ", number);
	orig = printf("[%d]\n", number);
	print_result(orig);

	number = 1234;
	printf("[%d]: ", number);
	orig = printf("[%d]\n", number);
	print_result(orig);

	number = -0;
	printf("[%d]: ", number);
	orig = printf("[%d]\n", number);
	print_result(orig);

	// LONG
	long nbr = 80000000001;

	printf(PURPLE"\nLONG TEST\n"UNCOLOR);
	printf("[%ld]: ", nbr);
	orig = printf("[%ld]\n", nbr);
	print_result(orig);

	nbr = 9223372036854775807;
	printf("[%ld]: ", nbr);
	orig = printf("[%ld]\n", nbr);
	print_result(orig);

	nbr = -9223372036854775807;
	printf("[%ld]: ", nbr);
	orig = printf("[%ld]\n", nbr);
	print_result(orig);

	nbr = 1234;
	printf("[%ld]: ", nbr);
	orig = printf("[%ld]\n", nbr);
	print_result(orig);

	nbr = -1234;
	printf("[%ld]: ", nbr);
	orig = printf("[%ld]\n", nbr);
	print_result(orig);

	nbr = 0;
	printf("[%ld]: ", nbr);
	orig = printf("[%ld]\n", nbr);
	print_result(orig);

	// FLOAT
	float flo = 25.02;

	printf(PURPLE"\nFLOAT TEST\n"UNCOLOR);
	printf("[%f]: ", flo);
	orig = printf("[%f]\n", flo);
	print_result(orig);

	flo = 25.0250509999;
	printf("[%f]: ", flo);
	orig = printf("[%f]\n", flo);
	print_result(orig);

	flo = 25.0;
	printf("[%f]: ", flo);
	orig = printf("[%f]\n", flo);
	print_result(orig);

	flo = -25.02505;
	printf("[%f]: ", flo);
	orig = printf("[%f]\n", flo);
	print_result(orig);

	flo = 0;
	printf("[%f]: ", flo);
	orig = printf("[%f]\n", flo);
	print_result(orig);

	// POINTER
	int intnbr = 25;
	int *pnt;

	pnt = &intnbr;
	printf(PURPLE"\nPOINTER TEST\n"UNCOLOR);
	printf("[%p]: ", pnt);
	orig = printf("[%p]\n", pnt);
	print_result(orig);
	
	
	//mine = ft_printf("%d", number);
	//printf("Expected: [%d]	output: [%s]\n", , "5");
	//print_OK(strcmp(printf("%d", number), "5"));
}

static void	flags(void)
{
	int	number;
	int orig;

	number = 5;
	printf(PURPLE"\nPRINT %% TEST\n"UNCOLOR);
	printf("this should print [%%]: ");
	orig = printf("[%%]\n");
	print_result(orig);

	printf(PURPLE"\n-+0# space TEST\n"UNCOLOR);
	// PRINT -
	printf("\nInput str: ");
	printf(YELLOW"[%%-d] : "UNCOLOR);
	printf("[%-d]\n", number);

	// PRINT 10
	printf("\nInput str: ");
	printf(YELLOW"[%%10d] : "UNCOLOR);
	printf("[%10d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%0d] : "UNCOLOR);
	printf("[%0d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%8d] : "UNCOLOR);
	printf("[%8d]\n", number);

	number = 1234567890;
	printf("\nInput str: ");
	printf(YELLOW"[%%10d] : "UNCOLOR);
	printf("[%10d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%0d] : "UNCOLOR);
	printf("[%0d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%8d] : "UNCOLOR);
	printf("[%8d]\n", number);

	// PRINT + PRINT WITH AND WITHOUT + flag
	number = 5;
	printf("\nInput str: ");
	printf(YELLOW"[%%+d] : "UNCOLOR);
	printf("[%+d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%-+d] : "UNCOLOR);
	printf("[%-+d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%786\t%%-786] : "UNCOLOR);
	printf("[%d\t%d]\n", 786, -786);

	printf("\nInput str: ");
	printf(YELLOW"[%%+786\t%%-786] : "UNCOLOR);
	printf("[%+d\t%+d]\n", 786, -786);

	// SPACE
	printf("\nInput str: \n");
	printf(YELLOW"[ 547] : "UNCOLOR);
	printf("[% d]\n", 547);
	printf(YELLOW"[-547] : "UNCOLOR);
	printf("[% d]\n", -547);

	// hashtag
	number = 31;
	printf("\nInput str: ");
	printf(YELLOW"[%%#o]\n"UNCOLOR);
	printf("[037] : ");
	printf("[%#o]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%#x]\n"UNCOLOR);
	printf("[0x1f] : ");
	printf("[%#x]\n", number);

	//printing with 0 flag - fills in leading zeros
	number = 452;
	printf("\nInput str: ");
	printf(YELLOW"[%%+09d]\n"UNCOLOR);
	printf("[+00000452] : ");
	printf("[%+09d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%09d]\n"UNCOLOR);
	printf("[000000452] : ");
	printf("[%09d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%% 9d]\n"UNCOLOR);
	printf("[ 452] : ");
	printf("[% 9d]\n", number);

	//using comma - thousand seperator display
	/*number = 58625;
	printf("\nInput str: ");
	printf(YELLOW"[%%,d]\n"UNCOLOR);
	printf("[58,625] : ");
	printf("[%,d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%,.2f]\n"UNCOLOR);
	printf("[58,625] : ");
	printf("[%,.2f]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%,.2f]\n"UNCOLOR);
	printf("[58,625] : ");
	printf("[%,.2f]\n",	number);*/

	// MIX
	number = 5;
	printf(PURPLE"\nmix\n"UNCOLOR);
	printf("\nInput str: ");
	printf(YELLOW"[%%-10d] : "UNCOLOR);
	printf("[%-10d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%010d] : "UNCOLOR);
	printf("[%010d]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%-#10x] : "UNCOLOR);
	printf("[%-#10x]\n", number);

	printf("\nInput str: ");
	printf(YELLOW"[%%#x] : "UNCOLOR);
	printf("[%#x]\n", number);
	//mine = ft_printf("%d", number);
	//printf("Expected: [%d]	output: [%s]\n", , "5");
	//print_OK(strcmp(printf("%d", number), "5"));

	printf(PURPLE"\nright justifying and left justifying\n"UNCOLOR);
	printf("0123456789012345678901234567890123456789\n");
	printf("\nInput str: ");
	//printf(YELLOW"[%10s%10d%10c%10f]\n"UNCOLOR, "hello", 7, 'a', );
	//printf("[%-10s%-10d%-10c%-10f]\n", "hello", 7, 'a', );
}

static void	csp(void)
{
	int	number;
	int orig;
	int mine;

	number = 5;
	printf("%d: ", number);
	orig = printf("%d\n", number);
	print_result(orig);
	printf("%f: ", 1234567.89);
	orig = printf("%'.2f\n", 1234567.89);
	print_result(orig);
	printf("%f: ", 1234567.8908);
	orig = printf("%'.2f\n", 1234567.8908);
	print_result(orig);
	printf("%f: ", 1234567.8);
	orig = printf("%'.2f\n", 1234567.8);
	print_result(orig);
	number = 8;
	printf(" %-10d \n", number);
	printf(" %010d \n", number);
	printf(" %-#10x \n", number);
	printf(" %#x \n", number);

	//mine = ft_printf("%d", number);
	//printf("Expected: [%d]	output: [%s]\n", , "5");
	//print_OK(strcmp(printf("%d", number), "5"));
}

static void	diouxX(void)
{
	int	number;
	int orig;
	int mine;

	number = 5;
	printf("%d: ", number);
	orig = printf("%d\n", number);
	print_result(orig);
	printf("%f: ", 1234567.89);
	orig = printf("%'.2f\n", 1234567.89);
	print_result(orig);
	printf("%f: ", 1234567.8908);
	orig = printf("%'.2f\n", 1234567.8908);
	print_result(orig);
	printf("%f: ", 1234567.8);
	orig = printf("%'.2f\n", 1234567.8);
	print_result(orig);
	number = 8;
	printf(" %-10d \n", number);
	printf(" %010d \n", number);
	printf(" %-#10x \n", number);
	printf(" %#x \n", number);
	//mine = ft_printf("%d", number);
	//printf("Expected: [%d]	output: [%s]\n", , "5");
	//print_OK(strcmp(printf("%d", number), "5"));
}

static void	f(void)
{
	int orig;

	printf("%f: ", 1234567.89);
	orig = printf("%'.2f\n", 1234567.89);
	print_result(orig);
	printf("%f: ", 1234567.8908);
	orig = printf("%'.2f\n", 1234567.8908);
	print_result(orig);
	printf("%f: ", 1234567.8);
	orig = printf("%'.2f\n", 1234567.8);
	print_result(orig);
	//mine = ft_printf("%d", number);
	//printf("Expected: [%d]	output: [%s]\n", , "5");
	//print_OK(strcmp(printf("%d", number), "5"));
}

int main(void)
{
	printf(PURPLE"simple test\n"UNCOLOR);
	simple();

	printf(PURPLE"\n-------\n\n"UNCOLOR);

	printf(PURPLE"flags test\n"UNCOLOR);
	flags();

	//printf(PURPLE"csp test\n"UNCOLOR);
	//csp();

	//printf(PURPLE"diouxX test\n"UNCOLOR);
	//diouxX();

	//printf(PURPLE"f test\n"UNCOLOR);
	//f();

	return (0);
}
