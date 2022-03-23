/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:56:27 by molesen           #+#    #+#             */
/*   Updated: 2022/03/23 10:56:29 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_space_zero_calc_digit(t_flag *flag, int len)
{
	char	zero;
	char	space;

	zero = '0';
	space = ' ';
	if (flag->prec < flag->width && flag->prec != -1 && (spec_check(flag, 'd', 'o', 'n') == TRUE))
	{
		while (len++ < flag->width)
			flag->ret += write(1, &space, 1);
	}
	else if (flag->prec >= 0 && flag->prec > len && flag->spec != 'f')
	{
		while (len++ < flag->prec)
			flag->ret += write(1, &zero, 1);
	}
	else if (flag->zero == '0' && flag->prec == -1 && flag->minus == '1')
	{
		while (len++ < flag->width)
			flag->ret += write(1, &zero, 1);
	}
	else
	{
		while (len++ < flag->width)
			flag->ret += write(1, &space, 1);
	}
}

void	ft_plus_print(char *str, t_flag *flag)
{
	char	space;
	char	minus;

	space = ' ';
	minus = '-';
	if (flag->spec != 'u' && str[0] != '-')
	{
		if (flag->plus == '+')
			flag->ret += write(1, &flag->plus, 1);
		else if ((flag->width != -1 && flag->zero != '0') || flag->space == ' ')
			flag->ret += write(1, &space, 1);
	}
	else if (str[0] == '-' && flag->spec != 'u')
	{
		flag->ret += write(1, &minus, 1);
		flag->plus = '1';
	}
}

static int	ft_len_calc(char *str, t_flag *flag)
{
	int	len;

	if (flag->spec == 's')
	{
		len = flag->prec;
		if (flag->prec == -1 || flag->prec == flag->width)
			len = ft_strlen(str);
	}
	else
	{
		len = ft_strlen(str);
	}
	return (len);
}

static void	ft_print_calc_helper(char *str, t_flag *flag, int len, void (*f)(t_flag *, int, char *))
{
	if (flag->minus == '-' && flag->prec < flag->width)
	{
		ft_prec_calc(str, flag);
		f(flag, len, str);
	}
	else
	{
		f(flag, len, str);
		ft_prec_calc(str, flag);
	}
}

void	ft_print_calc(char *str, t_flag *flag, void (*f)(t_flag *, int, char *))
{
	int	len;

	len = ft_len_calc(str, flag);
	if (str[0] == '-')
	{
		flag->plus = '+';
		if (flag->prec != -1 && (flag->prec < flag->width || flag->prec >= len))
			len--;
	}
	if (((flag->space == ' ' && flag->minus == '1') || flag->prec > flag->width || flag->zero == '0') && \
		(spec_check(flag, 'd', 'f', 'u') == TRUE))
		ft_plus_print(str, flag);
	else if ((spec_check(flag, 'o', 'x', 'X') == TRUE) && flag->width <= flag->prec)
		ft_prec_calc_ox(str, flag, TRUE);
	if (flag->width >= 0 || flag->prec >= 0)
		ft_print_calc_helper(str, flag, len, f);
	else
		ft_prec_calc(str, flag);
	ft_strdel(&str);
}
