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

/*
**	function called from str_print.c from function ft_cpy_to_temp_str
**	helps calculate how much of string should be copied into final string
*/

int	ft_str_i_calc(int len, t_flag *flag)
{
	int	dif;

	dif = flag->prec - len;
	if (dif < 0)
	{
		if (flag->prec == -1)
			return (len);
		return (flag->prec);
	}
	return (len);
}

/*	checks if any of the specifiers inputtet is correct	*/

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

static void	ft_flag_adjuster(t_flag *flag)
{
	if (flag->star == 'p' && flag->prec < -1)
	{
		flag->prec *= -1;
		flag->minus = '-';
	}
	if ((flag->star == 'w' || flag->star == 'p') && flag->width < -1)
	{
		flag->width *= -1;
		flag->minus = '-';
	}
	if (flag->prec >= flag->width && spec_check(flag, 'c', 's', 'p') == FALSE)
		flag->width = -1;
}

/*	narrows down correct specifier and resets i in main loop to correct pos	*/

int	ft_specifier_check(const char *format, t_flag *flag, va_list *arg)
{
	if (flag->prec >= 0)
		flag->zero = '1';
	if (flag->space == ' ' && flag->plus == '+')
		flag->space = '1';
	ft_flag_adjuster(flag);
	if (*format == 'c' || *format == 's' || *format == 'p')
		ft_csp_print(format, flag, arg);
	else if (*format == 'd' || *format == 'i' || *format == 'u')
		ft_diu_print(format, flag, arg);
	else if (*format == 'o' || *format == 'x' || *format == 'X')
		ft_ox_print(format, flag, arg);
	else if (*format == 'f' || *format == '%')
		ft_fp_print(format, flag, arg);
	else
		return (FALSE);
	ft_i_reset(format, flag);
	return (TRUE);
}
