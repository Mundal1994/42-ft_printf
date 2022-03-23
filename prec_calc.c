/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:12:51 by molesen           #+#    #+#             */
/*   Updated: 2022/03/14 19:12:53 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_prec_calc_ox(char *str, t_flag *flag, int first)
{
	char	space;

	space = ' ';
	if (first == TRUE)
	{
		if (flag->hash == TRUE && str[0] != '0' && str[1] != '\0')
			ft_hash_print(flag);
	}
	else if (flag->spec == 'o' && str[0] == '0' && str[1] == '\0' && flag->prec == 0 && flag->hash == FALSE)
	{
		if (flag->width > 0)
			flag->ret += write(1, &space, 1);
		return ;
	}
	else if (spec_check(flag, 'x', 'X', 'n') == TRUE && str[0] == '0' && str[1] == '\0' && flag->prec == 0)
	{
		if (flag->width > 0)
			flag->ret += write(1, &space, 1);
		return ;
	}
	else if (flag->spec == 'o' && flag->prec > (int)ft_strlen(str) && flag->prec < flag->width)
	{
		ft_zero_print(flag, str);
		flag->ret += write(1, str, ft_strlen(str));
	}
	else
		flag->ret += write(1, str, ft_strlen(str));
}

static void	ft_prec_calc_digit(char *str, t_flag *flag, int first)
{
	char	space;
	char	zero;

	space = ' ';
	zero = '0';
	if (first == TRUE)
	{
		if (flag->plus == '+' && ((flag->space == ' ' && flag->minus == '-') || flag->prec <= flag->width))
			if (flag->zero == '1')
				ft_plus_print(str, flag);
	}
	else
	{
		if (str[0] == '0' && str[1] == '\0')
		{
			ft_zero_print(flag, str);
			if (flag->prec > 0)
				flag->ret += write(1, str, ft_strlen(str));
			else if (flag->prec == 0 && flag->width > (int)ft_strlen(str))
				flag->ret += write(1, &space, 1);
		}
		else if (str[0] == '0' && str[1] == '\0' && flag->spec != 'f')
			flag->ret += write(1, &space, 1);
		else if (flag->spec == 'd' && flag->prec > (int)ft_strlen(str) && flag->prec < flag->width)
		{
			ft_zero_print(flag, str);
			flag->ret += write(1, str, ft_strlen(str));
		}
		else
			flag->ret += write(1, str, ft_strlen(str));
	}
}

static void	ft_prec_calc_csp(char *str, t_flag *flag)
{
	int		i;
	int		check;
	char	space;

	i = 0;
	space = ' ';
	check = TRUE;
	if (flag->prec < 2 && flag->spec == 'p')
		flag->prec = 2;
	if (flag->prec >= 0 && (int)ft_strlen(str) >= flag->prec)
	{
		while (i < flag->prec)
		{
			if (str[i] == '\0')
				check = FALSE;
			if (check == TRUE)
				flag->ret += write(1, &str[i++], 1);
			else
			{
				i++;
				flag->ret += write(1, &space, 1);
			}
		}
	}
	else if (flag->prec >= (int)ft_strlen(str) && str[0] == '\0')
	{
		if (flag->width != -1)
			ft_zero_print(flag, str);
	}
	else
	{
		while (str[i] != '\0')
			flag->ret += write(1, &str[i++], 1);
	}
}

void	ft_prec_calc(char *str, t_flag *flag)
{
	if (spec_check(flag, 'd', 'u', 'f') == TRUE)
		ft_prec_calc_digit(str, flag, TRUE);
	else if ((spec_check(flag, 'o', 'x', 'X') == TRUE) && flag->width > flag->prec)
		ft_prec_calc_ox(str, flag, TRUE);
	if (str[0] == '-' && flag->spec != 'c' && flag->spec != 's')
		str++;
	if (flag->prec == -1)
		flag->ret += write(1, str, ft_strlen(str));
	else
	{
		if (spec_check(flag, 'd', 'u', 'f') == TRUE)
			ft_prec_calc_digit(str, flag, FALSE);
		else if (spec_check(flag, 'o', 'x', 'X') == TRUE)
			ft_prec_calc_ox(str, flag, FALSE);
		else
			ft_prec_calc_csp(str, flag);
	}
}
