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

static int	ft_hhll_flag_check(const char *format, t_flag *flag, int on,
			int *pnt)
{
	if (*format == 'h' && format[1] == 'h')
	{
		flag->hh = on;
		*pnt += 1;
	}
	else if (*format == 'h')
		flag->h = on;
	else if (*format == 'l' && format[1] == 'l')
	{
		flag->ll = on;
		*pnt += 1;
	}
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

static int	ft_flag_check(const char *format, t_flag *flag, int on, int *pnt)
{
	if (*format == '-')
		flag->minus = '-';
	else if (*format == '+')
		flag->plus = '+';
	else if (*format == ' ')
		flag->space = ' ';
	else if (*format == '0' && format[-1] != '0')
		flag->zero = '0';
	else if (*format == '#')
		flag->hash = on;
	else
		return (FALSE);
	*pnt += 1;
	if (flag->plus == '+')
		flag->space = '1';
	if (flag->minus == '-' || flag->space == '0')
		flag->zero = '1';
	return (on);
}

static int	ft_flag_loop(const char *format, t_flag *flag, va_list *arg,
			int *pnt)
{
	int	specifier;

	specifier = FALSE;
	while (specifier == FALSE && ft_flag_check(&format[*pnt], flag, TRUE, pnt) \
		== TRUE)
		specifier = ft_specifier_check(&format[*pnt], flag, arg);
	while (specifier == FALSE && ft_isdigit(format[*pnt]) == 1)
	{
		ft_width_calc(&format[*pnt], &flag->width, pnt);
		specifier = ft_specifier_check(&format[*pnt], flag, arg);
	}
	while (specifier == FALSE && format[*pnt] == '.')
	{
		*pnt += 1;
		ft_width_calc(&format[*pnt], &flag->prec, pnt);
		specifier = ft_specifier_check(&format[*pnt], flag, arg);
	}
	if (specifier == FALSE && ft_hhll_flag_check(&format[*pnt], flag, TRUE, \
		pnt) == TRUE)
		specifier = ft_specifier_check(&format[*pnt], flag, arg);
	return (specifier);
}

void	ft_flag_checker(const char *format, t_flag *flag, va_list *arg)
{
	int	i;
	int	*pnt;
	int	specifier;
	char	c;

	i = 0;
	pnt = &i;
	c = '%';
	specifier = ft_specifier_check(&format[i], flag, arg);
	if (specifier == FALSE)
		specifier = ft_flag_loop(format, flag, arg, pnt);
	if (specifier == FALSE)
	{
		flag->ret += write(1, &c, 1);
		flag->i -= 1;
	}
}
