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

void	ft_hash_print(t_flag *flag)
{
	char	zero;
	char	x;
	char	big_x;

	zero = '0';
	x = 'x';
	big_x = 'X';
	flag->ret += write(1, &zero, 1);
	if (flag->spec == 'x')
		flag->ret += write(1, &x, 1);
	else if (flag->spec == 'X')
		flag->ret += write(1, &big_x, 1);
}

void	ft_zero_print(t_flag *flag, char *str)
{
	int		len;
	char	space;

	space = ' ';
	len = 0;
	if (spec_check(flag, 'c', 's', 'p') == TRUE)
	{
		while (len < flag->prec)
		{
			len++;
			flag->ret += write(1, &space, 1);
		}
	}
	else
	{
		len = ft_strlen(str);
		if (str[0] == '-' && flag->spec == 'o')
			len--;
		while (len < flag->prec)
		{
			ft_hash_print(flag);
			len++;
		}
	}
}

int	spec_check(t_flag *flag, int a, int b, int c)
{
	if (flag->spec == a)
		return (TRUE);
	else if (flag->spec == b)
		return (TRUE);
	else if (flag->spec == c)
		return (TRUE);
	return (FALSE);
}

static void	ft_prepare_flags(t_flag *flag, int c)
{
	if (flag->prec >= flag->width)
		flag->width = -1;
	if (c == 'o')
	{
		if (flag->zero == '0')
		{
			if (flag->width > 0)
			{
				flag->prec = flag->width;
				if (flag->hash == TRUE)
					flag->prec -= 2;
			}
			flag->zero = '1';
			flag->width = -1;
		}
	}
}

int	ft_specifier_check(const char *format, t_flag *flag, va_list *arg)
{
	if (flag->prec >= 0)
		flag->zero = '1';
	if (*format == 'c' || *format == 's' || *format == 'p')
		ft_csp_print(format, flag, arg);
	else if (*format == 'd' || *format == 'i' || *format == 'u')
	{
		ft_prepare_flags(flag, 'd');
		ft_diu_print(format, flag, arg);
	}
	else if (*format == 'o' || *format == 'x' || *format == 'X')
	{
		ft_prepare_flags(flag, 'o');
		ft_ox_print(format, flag, arg);
	}
	else if (*format == 'f' || *format == '%')
		ft_f_print(format, flag, arg);
	else
		return (FALSE);
	ft_i_reset(format, flag);
	return (TRUE);
}
