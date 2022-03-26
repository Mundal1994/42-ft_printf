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

/*	puts 0x into string	*/

void	*ft_hash_print(char *temp, t_flag *flag, int *index)
{
	ft_memset(temp, '0', 1);
	(*index)++;
	if (flag->spec == 'x')
	{
		(*index)++;
		ft_memset(&temp[1], 'x', 1);
	}
	if (flag->spec == 'X')
	{
		(*index)++;
		ft_memset(&temp[1], 'X', 1);
	}
	return (temp);
}

/*	checks if the conditions for putting hash has been meet	*/

void	*ft_hash_sign_check(char *temp, char *str, t_flag *flag, int *i)
{
	if (flag->minus == '-')
		ft_hash_print(temp, flag, i);
	else if (flag->zero == '0' && flag->width >= 0 && flag->prec == -1)
		ft_hash_print(temp, flag, i);
	else if (flag->width == -1 && flag->prec == -1)
		ft_hash_print(temp, flag, i);
	else if (flag->prec > (int)ft_strlen(str))
		ft_hash_print(temp, flag, i);
	else if (flag->prec < (int)ft_strlen(str) && flag->prec != -1 && \
		flag->width < (int)ft_strlen(str))
		ft_hash_print(temp, flag, i);
	return (temp);
}

/*	loops through string and changes either toupper or tolower	*/

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

/*	length converter for octal and hex	*/

static char	*ft_convert_length_ox(char *str, t_flag *flag,
			unsigned long long nbr)
{
	int	specifier;

	if (flag->spec == 'o')
		specifier = 8;
	else
		specifier = 16;
	if (flag->hh == TRUE)
		str = ft_ulltoa_base((unsigned char)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->h == TRUE)
		str = ft_ulltoa_base((unsigned short)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->l == TRUE)
		str = ft_ulltoa_base((unsigned long)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->ll == TRUE)
		str = ft_ulltoa_base(nbr, ft_ulong_len(nbr), specifier);
	else
		str = ft_ulltoa_base((unsigned int)nbr, ft_ulong_len(nbr), specifier);
	return (str);
}

/*	specifies specifier and gets arg	*/

void	ft_ox_print(const char *format, t_flag *flag, va_list *arg)
{
	unsigned long long	nbr;
	char				*str;

	nbr = va_arg(*arg, unsigned long long);
	str = NULL;
	if (*format == 'o')
	{
		flag->spec = 'o';
		str = ft_convert_length_ox(str, flag, nbr);
		ft_print_calc(str, flag, &ft_digit_print);
	}
	else if (*format == 'x')
	{
		flag->spec = 'x';
		str = ft_convert_length_ox(str, flag, nbr);
		ft_striter_uplow(str, &ft_tolower);
		ft_print_calc(str, flag, &ft_digit_print);
	}
	else if (*format == 'X')
	{
		flag->spec = 'X';
		str = ft_convert_length_ox(str, flag, nbr);
		ft_striter_uplow(str, &ft_toupper);
		ft_print_calc(str, flag, &ft_digit_print);
	}
}
