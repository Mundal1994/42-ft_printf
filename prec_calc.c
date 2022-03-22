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

static void	ft_hash_print(t_flag *flag)
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

void	ft_prec_calc_ox(char *str, t_flag *flag, int first)
{
	char	space;
	int		len;

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
	else if ((flag->spec == 'x' || flag->spec == 'X') && str[0] == '0' && str[1] == '\0' && flag->prec == 0)
	{
		if (flag->width > 0)
			flag->ret += write(1, &space, 1);
		return ;
	}
	else if (flag->spec == 'o' && flag->prec > (int)ft_strlen(str) && flag->prec < flag->width)
	{
		len = ft_strlen(str);
		while (len < flag->prec)
		{
			ft_hash_print(flag);
			len++;
		}
		flag->ret += write(1, str, ft_strlen(str));
	}
	else
		flag->ret += write(1, str, ft_strlen(str));
}

static void	ft_prec_calc_digit(char *str, t_flag *flag, int first)
{
	char	space;

	space = ' ';
	if (first == TRUE)
	{
		if (flag->plus == '+' && ((flag->space == ' ' && flag->minus == '-') || flag->prec <= flag->width))
			if (flag->zero == '1')
				ft_plus_print(str, flag);
	}
	else
	{
		if ((ft_strlen(str) == 0 || (str[0] == '0' && str[1] == '\0')) && flag->spec != 'f')
			flag->ret += write(1, &space, 1);
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
		while (i < flag->prec)
		{
			i++;
			flag->ret += write(1, &space, 1);
		}
	}
	else
	{
		while (str[i] != '\0')
			flag->ret += write(1, &str[i++], 1);
	}
}

void	ft_prec_calc(char *str, t_flag *flag)
{
	if (flag->spec == 'd' || flag->spec == 'u' || flag->spec == 'f')
		ft_prec_calc_digit(str, flag, TRUE);
	else if ((flag->spec == 'o' || flag->spec == 'x' || flag->spec == 'X') && flag->width > flag->prec)
		ft_prec_calc_ox(str, flag, TRUE);
	if (str[0] == '-')
		str++;
	if (flag->prec == -1)
		flag->ret += write(1, str, ft_strlen(str));
	else
	{
		if (flag->spec == 'd' || flag->spec == 'u' || flag->spec == 'f')
			ft_prec_calc_digit(str, flag, FALSE);
		else if (flag->spec == 'o' || flag->spec == 'x' || flag->spec == 'X')
			ft_prec_calc_ox(str, flag, FALSE);
		else
			ft_prec_calc_csp(str, flag);
	}
}
