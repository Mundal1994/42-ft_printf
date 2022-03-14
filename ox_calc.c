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

void	ft_space_calc_ox(t_flag *flag, int len)
{
	if (flag->hash == TRUE && (flag->width <= len || flag->prec <= len))
	{
		if (flag->spec == 'o')
			len++;
		else if (flag->spec != 'o' && flag->width > len)
			len += 2;
	}
	ft_space_zero_calc_digit(flag, len);
}

/*
static void	ft_prec_calc(char *str, t_flag *flag)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (flag->hash == TRUE && str[0] != '0')
		ft_hash_print(flag, str_len);
	if (flag->prec == -1)
	{
		ft_putstr(str);
		flag->len += str_len - 1;
	}
	else
	{
		if (flag->prec > str_len)
			ft_space_zero_calc(flag, str_len);
		ft_putstr(str);
		if (flag->width >= 0 && flag->prec < flag->width)
			flag->len += flag->width - 1;
		else if (flag->prec <= str_len)
			flag->len += str_len - 1;
		else
			flag->len += flag->prec - 1;
	}
}*/

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

static void	ft_oxtoa_helper(char *str, unsigned long long nbr, int base)
{
	int	digit;

	digit = 0;
	if (nbr == 0)
		*str++ = '0';
	else
	{
		while (nbr)
		{
			digit = nbr % base;
			if (digit > 9)
				*str = 'A' + digit - 10;
			else
				*str = '0' + digit;
			nbr = nbr / base;
			str++;
		}
	}
	*str = '\0';
}

char	*ft_oxtoa_base(unsigned long long nbr, int len, int base)
{
	char	*str;

	str = ft_strnew(len);
	ft_oxtoa_helper(str, nbr, base);
	ft_strrev(str);
	return (str);
}

static char	*ft_convert_length_ox(char *str, t_flag *flag, unsigned long long nbr, int c)
{
	int	specifier;

	if (c == 'o')
		specifier = 8;
	else
		specifier = 16;
	if (flag->hh == TRUE)
		str = ft_oxtoa_base((unsigned char)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->h == TRUE)
		str = ft_oxtoa_base((unsigned short)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->l == TRUE)
		str = ft_oxtoa_base((unsigned long)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->ll == TRUE)
		str = ft_oxtoa_base(nbr, ft_ulong_len(nbr), specifier);
	else
		str = ft_oxtoa_base((unsigned int)nbr, ft_ulong_len(nbr), specifier);
	return (str);
}

void	ft_oxX_print(const char *format, t_flag *flag, va_list *arg)
{
	unsigned long long	nbr;
	char				*str;

	nbr = va_arg(*arg, unsigned long long);
	str = NULL;
	if (*format == 'o')
	{
		flag->spec = 'o';
		str = ft_convert_length_ox(str, flag, nbr, 'o');
		ft_print_calc(str, flag, &ft_space_calc_ox);
	}
	else if (*format == 'x')
	{
		flag->spec = 'x';
		str = ft_convert_length_ox(str, flag, nbr, 'x');
		ft_striter_uplow(str, &ft_tolower);
		ft_print_calc(str, flag, &ft_space_calc_ox);
	}
	else if (*format == 'X')
	{
		flag->spec = 'X';
		str = ft_convert_length_ox(str, flag, nbr, 'X');
		ft_striter_uplow(str, &ft_toupper);
		ft_print_calc(str, flag, &ft_space_calc_ox);
	}
}
