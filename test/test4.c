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
/*
void	print_OK(int result)
{
	if (result != 0)
		printf(RED"				KO!\n\n"UNCOLOR);
	else
		printf(GREEN"				OK!\n\n"UNCOLOR);
}
*/

static void	percentage_print(void)
{
	int orig;
	printf(PURPLE"\nPRINT %% TEST\n"UNCOLOR);

	printf("this should print [%%]: ");
	orig = printf("[%%]\n");
	print_result(orig);
}

static void	hashtag(void)
{
	int number;
	printf(PURPLE"\nHASHTAG TEST\n"UNCOLOR);
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
}

static void	minus(void)
{
	int	number;

	printf(PURPLE"\nMINUS TEST\n"UNCOLOR);
	// PRINT -
	printf("expected [%%-d] : ");
	printf("[%-d]\n", number);
}

static void	plus(void)
{
	int	number;

	// PRINT + PRINT WITH AND WITHOUT + flag
	printf(PURPLE"\nPLUS TEST\n"UNCOLOR);
	number = 5;
	printf("\nInput str: ");
	printf("[%%+d] : ");
	printf("[%+d]\n", number);

	printf("\nInput str: ");
	printf("[%%-+d] : ");
	printf("[%-+d]\n", number);

	printf("\nInput str: ");
	printf("[%%786\t%%-786] : ");
	printf("[%d\t%d]\n", 786, -786);

	printf("\nInput str: ");
	printf("[%%+786\t%%-786] : ");
	printf("[%+d\t%+d]\n", 786, -786);
}

static void	print_10(void)
{
	int number;
	// PRINT 10
	printf(PURPLE"\n0 TEST\n"UNCOLOR);
	printf("\nInput str: ");
	printf("[%%10d] : ");
	printf("[%10d]\n", number);

	printf("\nInput str: ");
	printf("[%%0d] : ");
	printf("[%0d]\n", number);

	printf("\nInput str: ");
	printf("[%%8d] : ");
	printf("[%8d]\n", number);

	number = 1234567890;
	printf("\nInput str: ");
	printf("[%%10d] : ");
	printf("[%10d]\n", number);

	printf("\nInput str: ");
	printf("[%%0d] : ");
	printf("[%0d]\n", number);

	printf("\nInput str: ");
	printf("[%%8d] : ");
	printf("[%8d]\n", number);

	//printing with 0 flag - fills in leading zeros
	number = 452;
	printf("\nInput str: ");
	printf("[%%+09d]\n");
	printf("[+00000452] : ");
	printf("[%+09d]\n", number);

	printf("\nInput str: ");
	printf("[%%09d]\n");
	printf("[000000452] : ");
	printf("[%09d]\n", number);

	printf("\nInput str: ");
	printf("[%% 9d]\n");
	printf("[ 452] : ");
	printf("[% 9d]\n", number);
}

static void	space(void)
{
	//SPACE
	printf(PURPLE"\nSPACE TEST\n"UNCOLOR);
	printf("\nInput str: \n");
	printf("[ 547] : ");
	printf("[% d]\n", 547);
	printf("[-547] : ");
	printf("[% d]\n", -547);
}

static void	mix(void)
{
	int	number;
	// MIX
	number = 5;
	printf(PURPLE"\nMIX TEST\n"UNCOLOR);
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

int main(void)
{
	printf(PURPLE"Percentage_print test\n"UNCOLOR);
	percentage_print();

	printf(PURPLE"\n-------\n\n"UNCOLOR);

	printf(PURPLE"hashtag test\n"UNCOLOR);
	hashtag();

	printf(PURPLE"\n-------\n\n"UNCOLOR);

	printf(PURPLE"print 10 test\n"UNCOLOR);
	print_10();

	printf(PURPLE"\n-------\n\n"UNCOLOR);

	printf(PURPLE"minus test\n"UNCOLOR);
	minus();

	printf(PURPLE"\n-------\n\n"UNCOLOR);

	printf(PURPLE"plus test\n"UNCOLOR);
	plus();

	printf(PURPLE"\n-------\n\n"UNCOLOR);

	printf(PURPLE"space test\n"UNCOLOR);
	space();

	printf(PURPLE"\n-------\n\n"UNCOLOR);

	printf(PURPLE"mix test\n"UNCOLOR);
	mix();
}