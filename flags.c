/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:00:28 by molesen           #+#    #+#             */
/*   Updated: 2022/02/22 13:00:30 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hhll_flag_check(const char *format, t_flag *flag, int on)
{
	if (*format == 'h' && format[1] == 'h')
		flag->hh = on;
	else if (*format == 'h')
		flag->h = on;
	else if (*format == 'l' && format[1] == 'l')
		flag->ll = on;
	else if (*format == 'l')
		flag->l = on;
	else if (*format == 'L')
		flag->b_l = on;
	else
		return (FALSE);
	return (TRUE);
}

int	ft_flag_check(const char *format, t_flag *flag, int on)
{
	if (*format == '-')
		flag->minus = on;
	else if (*format == '+')
		flag->plus = on;
	else if (*format == ' ')
		flag->space = on;
	else if (*format == '0')
		flag->zero = on;
	else if (*format == '#')
		flag->hash = on;
	else if (ft_isdigit(*format) == 1)
		flag->width = *format - '0';
	else if (*format == '.' && ft_isdigit(format[1]) == 1)
	{
		flag->hash = on;
		ft_flag_check("0", flag, FALSE);
		ft_flag_check("#", flag, FALSE);
		ft_flag_check("+", flag, FALSE);
		ft_flag_check(" ", flag, FALSE);
	}
	else
	{
		if (ft_hhll_flag_check(format, flag, TRUE) == FALSE)
		{
			ft_putstr("error\n");
			exit (1);
		}
	}
	return (on);
}