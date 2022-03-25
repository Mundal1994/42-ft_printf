/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:20:07 by molesen           #+#    #+#             */
/*   Updated: 2022/03/24 20:20:09 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_flags_ox(char *str, t_flag *flag, int total, int len)
{
	if (ft_strcmp(str, "0") == 0 && flag->width < flag->prec && flag->prec == 0)
	{
		if (flag->spec == 'o' && flag->hash == TRUE)
			return (1);
		return (0);
	}
	if (flag->hash == TRUE)
	{
		if (flag->width == -1 && flag->prec == -1 && ft_strcmp(str, "0") == 0)
			return (total);
		if (flag->width < len || flag->prec > len)
		{
			if (flag->spec == 'o')
			{
				if (flag->prec <= len)
					return (++total);
				if (flag->width < flag->prec)
					return (total);
			}
			total++;
			if (spec_check(flag, 'n', 'x', 'X') == TRUE)
				total++;
		}
	}
	return (total);
}

static int	ft_check_flags(char *str, t_flag *flag, int total, int len)
{
	if (spec_check(flag, 'o', 'x', 'X') == TRUE)
		return (ft_check_flags_ox(str, flag, total, len));
	if (spec_check(flag, 'd', 'n', 'f') == TRUE)
	{
		if (!(len > flag->width && len > flag->prec && (str[0] == '-' || str[0] == '+')))
			if (flag->width < len)
				return (ft_check_flags_digit(str, flag, total, len));
	}
	return (total);
}

static int	ft_len_calculator(t_flag *flag, int len)
{
	if (flag->width == -1 && flag->prec == -1)
		return (len);
	else if (flag->prec > flag->width && flag->spec == 'f')
		return (len);
	else if (flag->width < len && flag->prec == -1 && spec_check(flag, 'c', 's', 'n') == TRUE)
		return (len);
	else if (flag->width > flag->prec && (flag->width > len || spec_check(flag, 'c', 's', 'n') == TRUE))
		return (flag->width);
	else if (flag->prec > len && flag->width == -1)
	{
		if (spec_check(flag, 'c', 's', 'n') == TRUE)
			return (len);
		else
			return (flag->prec);
	}
	else if (flag->prec >= flag->width && (flag->prec >= len || spec_check(flag, 'c', 's', 'p') == TRUE))
	{
		if (spec_check(flag, 'c', 's', 'p') == TRUE && flag->prec > len)
			return (flag->width);
		return (flag->prec);
	}
	return (len);
}

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

void	ft_print_calc(char *str, t_flag *flag, void (*f)(char *, t_flag *, int, int))
{
	int		len;
	int		total;

	len = ft_strlen(str);
	total = ft_len_calculator(flag, len);
	total = ft_check_flags(str, flag, total, len);
	f(str, flag, len, total);
}
