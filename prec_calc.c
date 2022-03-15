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

static void	ft_hash_print(t_flag *flag, int len)
{
	if (flag->spec == 'o')
	{
		if (flag->width <= len || flag->prec <= len)
			ft_putchar('0');
		if (flag->width == -1 && flag->prec == -1)
			flag->len++;
		else if (flag->width <= len && flag->prec <= len)
			flag->len++;
	}
	else
	{
		if (flag->spec == 'x')
			ft_putstr("0x");
		else
			ft_putstr("0X");
		if ((flag->width <= len && flag->prec > len) || flag->width <= flag->prec)
			flag->len += 2;
	}
}

static void	ft_prec_calc_ox(char *str, t_flag *flag, int *str_len, int first)
{
	if (first == TRUE)
	{
		if (flag->hash == TRUE && str[0] != '0')
			ft_hash_print(flag, *str_len);
	}
	else
	{
		if (flag->prec > *str_len)
			ft_space_calc_ox(flag, *str_len);
		ft_putstr(str);
		if (flag->width >= 0 && flag->prec < flag->width)
			flag->len += flag->width - 1;
		else if (flag->prec <= *str_len)
			flag->len += *str_len - 1;
		else
			flag->len += flag->prec - 1;
	}
}

static void	ft_prec_calc_digit(char *str, t_flag *flag, int *str_len, int first)
{
	if (first == TRUE)
	{
		if (str[0] == '0' && flag->prec != -1)
			*str_len = 0;
		if (flag->plus == TRUE || (flag->space == TRUE && flag->minus == TRUE))
			ft_plus_print(flag, *str_len);
	}
	else
	{
		if (flag->prec > *str_len)
			ft_space_calc_digit(flag, *str_len);
		if (*str_len == 0)
			ft_putchar(' ');
		else
			ft_putstr(str);
		if (flag->width >= 0 && flag->prec < flag->width && flag->width > *str_len)
			flag->len += flag->width - 1;
		else if (flag->prec <= *str_len)
			flag->len += *str_len - 1;
		else
			flag->len += flag->prec - 1;
	}
}

static void	ft_prec_calc_csp(char *str, t_flag *flag)
{
	int	i;

	i = 0;
	while (i < flag->prec && str[i] != '\0')
		ft_putchar(str[i++]);
	if (flag->width >= 0 && flag->prec < flag->width)
		flag->len += flag->width - 1;
	else
		flag->len += flag->prec - 1;
}

void	ft_prec_calc(char *str, t_flag *flag)
{
	int	str_len;
	int	*pnt;

	pnt = &str_len;
	*pnt = ft_strlen(str);
	if (flag->spec == 'd' || flag->spec == 'u' || flag->spec == 'f')
		ft_prec_calc_digit(str, flag, pnt, TRUE);
	else if (flag->spec == 'o' || flag->spec == 'x' || flag->spec == 'X')
		ft_prec_calc_ox(str, flag, pnt, TRUE);
	if (flag->prec == -1)
	{
		ft_putstr(str);
		flag->len += *pnt - 1;
	}
	else
	{
		if (flag->spec == 'd' || flag->spec == 'u' || flag->spec == 'f')
			ft_prec_calc_digit(str, flag, pnt, FALSE);
		else if (flag->spec == 'o' || flag->spec == 'x' || flag->spec == 'X')
			ft_prec_calc_ox(str, flag, pnt, FALSE);
		else
			ft_prec_calc_csp(str, flag);
	}
}
