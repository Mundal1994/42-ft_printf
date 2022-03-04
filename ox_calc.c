/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ox_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:05:12 by molesen           #+#    #+#             */
/*   Updated: 2022/03/04 10:05:14 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_space_zero_calc(t_flag *flag, int len, int c)
{
	if (flag->hash == TRUE && (flag->width <= len || flag->prec <= len))
	{
		if (c == 'o')
			len++;
		else if (c != 'o' && flag->width > len)
			len += 2;
	}
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

static void	ft_hash_print(t_flag *flag, int len, int c)
{
	if (c == 'o')
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
		if (c == 'x')
			ft_putstr("0x");
		else
			ft_putstr("0X");
		if ((flag->width <= len && flag->prec > len) || flag->width <= flag->prec)
			flag->len += 2;
	}
}

static void	ft_prec_calc(char *str, t_flag *flag, int c)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (flag->hash == TRUE && str[0] != '0')
		ft_hash_print(flag, str_len, c);
	if (flag->prec == -1)
	{
		ft_putstr(str);
		flag->len += str_len - 1;
	}
	else
	{
		if (flag->prec > str_len)
			ft_space_zero_calc(flag, str_len, c);
		ft_putstr(str);
		if (flag->width >= 0 && flag->prec < flag->width)
			flag->len += flag->width - 1;
		else if (flag->prec <= str_len)
			flag->len += str_len - 1;
		else
			flag->len += flag->prec - 1;
	}
}

static void	ft_ox_flag_calc(const char *format, char *str, t_flag *flag, int c)
{
	int	len;

	len = ft_strlen(str);
	if (flag->prec != -1 && flag->prec > len)
		len = flag->prec;
	if (flag->width >= 0)
	{
		if (flag->width >= len && flag->prec == -1)
			flag->len += flag->width - len;
		if (flag->minus == TRUE)
		{
			ft_prec_calc(str, flag, c);
			ft_space_zero_calc(flag, len, c);
		}
		else
		{
			ft_space_zero_calc(flag, len, c);
			ft_prec_calc(str, flag, c);
		}
	}
	else
		ft_prec_calc(str, flag, c);
	ft_i_reset(format, flag);
}

static void	ft_striter_uplow(char *str, int (*f)(int))
{
	int	i;

	i = 0;
	if (str && f)
	{
		while (str[i] != '\0')
		{
			str[i] = f(str[i]);
			i++;
		}
	}
}

void	ft_oxX_print(const char *format, t_flag *flag, va_list *arg)
{
	int		nbr;
	char	*str;

	nbr = va_arg(*arg, int);
	if (*format == 'o')
	{
		str = ft_itoa_base(nbr, ft_int_len(nbr), 8);
		ft_ox_flag_calc(format, str, flag, 'o');
	}
	else if (*format == 'x')
	{
		str = ft_itoa_base(nbr, ft_int_len(nbr), 16);
		ft_striter_uplow(str, &ft_tolower);
		ft_ox_flag_calc(format, str, flag, 'x');
	}
	else if (*format == 'X')
	{
		str = ft_itoa_base(nbr, ft_int_len(nbr), 16);
		ft_striter_uplow(str, &ft_toupper);
		ft_ox_flag_calc(format, str, flag, 'X');
	}
	//if minus - problem with octal or doesn't return properly with the \0
}
