/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:00:37 by molesen           #+#    #+#             */
/*   Updated: 2022/02/22 13:00:39 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_space_zero_calc_digit(t_flag *flag, int len)
{
	char	zero;
	char	space;

	zero = '0';
	space = ' ';
	if (flag->prec >= 0 && flag->prec > len && flag->spec != 'f')
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

	space = ' ';
	if (flag->spec != 'u')
	{
		if (flag->plus == '+')
			flag->ret += write(1, &flag->plus, 1);
		else if (flag->width != -1 || (flag->space == ' ' && str[0] != '-'))
			flag->ret += write(1, &space, 1);
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
		if (flag->prec != -1 && flag->prec > len)
			len = flag->prec;
	}
	return (len);
}

void	ft_print_calc(char *str, t_flag *flag, void (*f)(t_flag *, int))
{
	int	len;

	len = ft_len_calc(str, flag);
	if (flag->space == ' ' && flag->minus == '1' && \
		(flag->spec == 'd' || flag->spec == 'f' || flag->spec == 'u'))
		ft_plus_print(str, flag);
	if (flag->width >= 0)
	{

		if (flag->minus == '-')
		{
			ft_prec_calc(str, flag);
			f(flag, len);
		}
		else
		{
			f(flag, len);
			ft_prec_calc(str, flag);
		}
	}
	else
		ft_prec_calc(str, flag);
	ft_strdel(&str);
}

int	ft_specifier_check(const char *format, t_flag *flag, va_list *arg)
{
	if (*format == 'c' || *format == 's' || *format == 'p')
	{
		ft_csp_print(format, flag, arg);
		ft_i_reset(format, flag);
		return (TRUE);
	}
	else if (*format == 'd' || *format == 'i' || *format == 'u')
	{
		ft_diu_print(format, flag, arg);
		ft_i_reset(format, flag);
		return (TRUE);
	}
	else if (*format == 'o' || *format == 'x' || *format == 'X')
	{
		ft_ox_print(format, flag, arg);
		ft_i_reset(format, flag);
		return (TRUE);
	}
	else if (*format == 'f' || *format == 'b' || *format == '%')
	{
		ft_f_print(format, flag, arg);
		ft_i_reset(format, flag);
		return (TRUE);
	}
	return (FALSE);
}
