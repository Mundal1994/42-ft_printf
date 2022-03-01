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

static int	ft_hhll_flag_check(const char *format, t_flag *flag, int on, int *pnt)
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
	*pnt += 1;
	return (TRUE);
}

static void	ft_width_calc(const char *format, int *digit, int *pnt)
{
	int	i;
	int	nbr;
	int	first;

	i = 0;
	first = TRUE;
	*digit = 0;
	while (ft_isdigit(format[i]) == 1)
	{
		if (first == FALSE)
			*digit *= 10;
		nbr = format[i++] - '0';
		*digit += nbr;
		first = FALSE;
	}
	*pnt += i;
}

static void	ft_precision_calc(const char *format, t_flag *flag, int *pnt)
{
	*pnt += 1;
	ft_width_calc(&format[1], &flag->prec, pnt);
}

static int	ft_flag_check(const char *format, t_flag *flag, int on, int *pnt)
{
	if (*format == '-')
		flag->minus = on;
	else if (*format == '+')
		flag->plus = on;
	else if (*format == ' ')
		flag->space = on;
	else if (*format == '0' && format[-1] != '0')
		flag->zero = on;
	else if (*format == '#')
		flag->hash = on;
	else
		return (FALSE);
	*pnt += 1;
	if (flag->plus == TRUE)
		flag->space = FALSE;
	return (on);
}

void	ft_convert_checker(const char *format, t_flag *flag, va_list *arg)
{
	int	i;
	int	*pnt;
	int	specifier;

	i = 0;
	pnt = &i;
	specifier = ft_convert_symbol(&format[i], flag, arg);
	if (specifier == FALSE)
	{
		flag->flags = TRUE;
		while (specifier == FALSE && ft_flag_check(&format[i], flag, TRUE, pnt) == TRUE)
			specifier = ft_convert_symbol(&format[i], flag, arg);
		while (specifier == FALSE && ft_isdigit(format[i]) == 1)
		{
			ft_width_calc(&format[i], &flag->width, pnt);
			specifier = ft_convert_symbol(&format[i], flag, arg);
		}
		while (specifier == FALSE && format[i] == '.')
		{
			ft_precision_calc(&format[i], flag, pnt);
			specifier = ft_convert_symbol(&format[i], flag, arg);
		}
		while (specifier == FALSE && ft_hhll_flag_check(&format[i], flag, TRUE, pnt) == TRUE)
			specifier = ft_convert_symbol(&format[i], flag, arg);
	}
}
