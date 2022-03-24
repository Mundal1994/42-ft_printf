/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 09:36:03 by molesen           #+#    #+#             */
/*   Updated: 2022/03/15 09:36:31 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	finds length of double
*/

long	ft_flong_len(double nbr)
{
	long	counter;

	counter = 0;
	if (nbr == 0)
		return (1);
	while (nbr >= 1)
	{
		nbr /= 10;
		counter++;
	}
	return (counter);
}

/*
**	converts to correct float based on flags
*/

static char	*ft_convert_length_f(char *str, t_flag *flag, double number, long double b_nbr)
{
	if (flag->prec != -1)
	{
		if (flag->b_l)
			str = ft_ftoa(b_nbr, flag->prec);
		else
			str = ft_ftoa((double)number, flag->prec);
	}
	else
	{
		if (flag->b_l)
			str = ft_ftoa(b_nbr, 6);
		else
			str = ft_ftoa((double)number, 6);
	}
	return (str);
}

/*
**	percentage calculator
*/

static void	ft_percentage_print(const char *format, t_flag *flag)
{
	char	*str;

	str = NULL;
	if (*format == '%')
	{
		flag->spec = 'u';
		str = ft_strnew(1);
		str[0] = '%';
		ft_print_calc(str, flag, &ft_digit_print);
	}
}

/*
**	float argv is taken
*/

void	ft_f_print(const char *format, t_flag *flag, va_list *arg)
{
	double				number;
	long double			b_number;
	char				*str;

	str = NULL;
	if (*format == 'f')
	{
		b_number = -1;
		number = -1;
		flag->spec = 'f';
		if (flag->b_l == TRUE)
		{
			b_number = va_arg(*arg, long double);
			str = ft_convert_length_f(str, flag, number, b_number);
		}
		else
		{
			number = va_arg(*arg, double);
			str = ft_convert_length_f(str, flag, number, b_number);
		}
		ft_print_calc(str, flag, &ft_digit_print);
	}
	else
		ft_percentage_print(format, flag);
	//make sure to round up / down the number depending on len i have provided...
}
