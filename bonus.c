/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:10:09 by molesen           #+#    #+#             */
/*   Updated: 2022/03/14 16:10:10 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_color_check(const char *str, int len)
{
	if (ft_strncmp(str, "reset", len) == 0)
		ft_putstr("\033[0m");
	else if (ft_strncmp(str, "bold", len) == 0)
		ft_putstr("\033[1m");
	else if (ft_strncmp(str, "red", len) == 0)
		ft_putstr("\033[31m");
	else if (ft_strncmp(str, "green", len) == 0)
		ft_putstr("\033[32m");
	else if (ft_strncmp(str, "yellow", len) == 0)
		ft_putstr("\033[33m");
	else if (ft_strncmp(str, "blue", len) == 0)
		ft_putstr("\033[34m");
	else if (ft_strncmp(str, "purple", len) == 0)
		ft_putstr("\033[35m");
	else if (ft_strncmp(str, "cyan", len) == 0)
		ft_putstr("\033[36m");
	else if (ft_strncmp(str, "white", len) == 0)
		ft_putstr("\033[37m");
	else if (ft_strncmp(str, "uncolor", len) == 0)
		ft_putstr("\033[39m");
	else
		return (FALSE);
	return (TRUE);
}

int	ft_color_print(const char *str, t_flag *flag)
{
	int	len;

	len = ft_strlen_stop((char *)str, '}');
	if (ft_color_check(str, len) == FALSE)
		return (FALSE);
	flag->i += len;
	return (TRUE);
}

static char	*ft_binary_to_str(unsigned int number)
{
	unsigned int	start;
	char			*str;
	int				count;

	start = number;
	count = 0;
	ft_putnbr(5);
	while (start >> 1)
	{
		ft_putnbr(count);
		ft_putchar('\n');
		count++;
	}
	str = ft_strnew(count);
	count = 0;
	ft_putnbr(5);
	start = number;
	while (start)
	{
		number = start;
		while (number >> 1)
		if (number & 1)
		{
			str[count] = '1';
			count++;
			ft_putnbr(5);
		}
		else
		{
			str[count] = '0';
			count++;
		}
		ft_putnbr(4);
		start = start >> 1;
	}
	return (str);
	/*if (number & 1)
		ft_putnbr(1);
	else
		ft_putnbr(0);*/
	//ft_putnbr((number & 1) ? '1' : '0');
}

void	ft_b_print(const char *format, t_flag *flag, va_list *arg)
{
	unsigned int		nbr;
	char				*str;

	str = NULL;
	nbr = 0;
	if (*format == 'b')
	{
		nbr = va_arg(*arg, unsigned int);
		if (flag)
			flag->spec = 'b';
		str = ft_binary_to_str(nbr);
		ft_putstr(str);
		/*str = ft_convert_length(str, flag, nbr);
		flag->spec = 'd';
		ft_print_calc(str, flag, &ft_space_calc_digit);*/
	}
	else if (*format == '%')
	{
		flag->spec = 'u';
		str = ft_strnew(1);
		str[0] = '%';
		ft_print_calc(str, flag, &ft_space_calc_digit);
	}
}
/*need to fix binary but also new test case with float*/