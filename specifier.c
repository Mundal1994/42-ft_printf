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
	if (flag->prec >= 0 && flag->prec > len)
	{
		while (len++ < flag->prec)
			ft_putchar('0');
	}
	else if (flag->zero == TRUE && flag->prec == -1 && flag->minus == FALSE)
	{
		while (len++ < flag->width)
			ft_putchar('0');
	}
	else
	{
		while (len++ < flag->width)
			ft_putchar(' ');
	}
}

void	ft_plus_print(t_flag *flag, int len)
{
	if (flag->spec != 'u')
	{
		if (flag->plus == TRUE)
			ft_putchar('+');
		else
			ft_putchar(' ');
		if (flag->width < len && flag->prec == -1)
			flag->len++;
		else if (flag->prec == -1)
			return ;
		else
			flag->len++;
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
	if (flag->space == TRUE && flag->minus == FALSE && \
		(flag->spec == 'd' || flag->spec == 'f' || flag->spec == 'u'))
		ft_plus_print(flag, len);
	if (flag->width >= 0)
	{
		if (flag->width >= len && flag->prec == -1)
			flag->len += flag->width - len;
		if (flag->minus == TRUE)
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
		ft_oxX_print(format, flag, arg);
		ft_i_reset(format, flag);
		return (TRUE);
	}
	else if (*format == 'f' || *format == 'b')
	{
		ft_f_print(format, flag, arg);
		ft_i_reset(format, flag);
		return (TRUE);
	}
	return (FALSE);
}
