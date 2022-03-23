/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:47:19 by molesen           #+#    #+#             */
/*   Updated: 2022/03/01 12:47:21 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	calculate the amount of space we need to consider when printing digits
**	narrows down what extra needs to be printed to have correct width
*/

void	ft_space_calc_digit(t_flag *flag, int len, char *str)
{
	int		dif;

	dif = 0;
	if (str[0] == '-' && flag->prec > len && flag->spec != 'u')
		dif = flag->prec - len + 1;
	else if (flag->spec != 'u')
		dif = flag->prec - len;
	if (flag->plus == '+' && flag->spec != 'u' && str[0] != '-' && (flag->prec < len || flag->width > flag->prec))
		len++;
	if (flag->space == ' ' && flag->spec != 'u' && (flag->prec < len || flag->width > flag->prec))
		len++;
	if (str[0] == '-' && (flag->prec < len || flag->width > flag->prec) && flag->prec <= 1 && flag->prec != -1)
		len++;
	if (flag->prec < flag->width && flag->prec != -1 && dif > 0 && (flag->spec == 'o' || flag->spec == 'd'))
		len += dif;
	ft_space_zero_calc_digit(flag, len);
}

/*	convert long long down to wanted length based on flags	*/

static char	*ft_convert_length(char *str, t_flag *flag, long long nbr)
{
	if (flag->hh == TRUE)
		str = ft_itoa_base((signed char)nbr, ft_long_len(nbr), 10);
	else if (flag->h == TRUE)
		str = ft_itoa_base((short)nbr, ft_long_len(nbr), 10);
	else if (flag->l == TRUE)
		str = ft_itoa_base((long)nbr, ft_long_len(nbr), 10);
	else if (flag->ll == TRUE)
		str = ft_itoa_base(nbr, ft_long_len(nbr), 10);
	else
		str = ft_itoa_base((int)nbr, ft_long_len(nbr), 10);
	return (str);
}

/*	convert unsigned long long down to wanted length based on flags	*/

static char	*ft_convert_length_u(char *str, t_flag *flag, unsigned long long \
nbr)
{
	str = ft_strnew(ft_ulong_len(nbr));
	if (flag->hh == TRUE)
		str = ft_ulltoa((unsigned char)nbr, str);
	else if (flag->h == TRUE)
		str = ft_ulltoa((unsigned short)nbr, str);
	else if (flag->l == TRUE)
		str = ft_ulltoa((unsigned long)nbr, str);
	else if (flag->ll == TRUE)
		str = ft_ulltoa(nbr, str);
	else
		str = ft_ulltoa((unsigned int)nbr, str);
	return (str);
}

/*	narrows down the specifier and start calculation for printing	*/

void	ft_diu_print(const char *format, t_flag *flag, va_list *arg)
{
	long long			nbr;
	unsigned long long	var;
	char				*str;

	str = NULL;
	nbr = 0;
	if (*format == 'd' || *format == 'i')
	{
		nbr = va_arg(*arg, long long);
		str = ft_convert_length(str, flag, nbr);
		flag->spec = 'd';
		ft_print_calc(str, flag, &ft_space_calc_digit);
	}
	else if (*format == 'u')
	{
		var = va_arg(*arg, unsigned long long);
		str = ft_convert_length_u(str, flag, var);
		flag->spec = 'u';
		ft_print_calc(str, flag, &ft_space_calc_digit);
	}
}
