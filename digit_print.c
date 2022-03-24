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

static int	ft_check_float_flags(char *str, t_flag *flag, int total, int len)
{
	if (flag->prec < len && flag->width == -1)
	{
		if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
			total++;
	}
	else if (flag->width <= len)
	{
		if (str[0] == '-' && (flag->width > -1 || flag->prec > -1))
			total++;
		else if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
			total++;
	}
	return (total);
}
static int	ft_check_flags_digit(char *str, t_flag *flag, int total, int len)
{
	if (flag->spec == 'f')
		return (ft_check_float_flags(str, flag, total, len));
	//else if (spec_check(flag, 'o', 'x', 'X') == TRUE && flag->hash == TRUE)
	//	total++;
	else
	{
		if ((flag->width <= len && flag->width <= flag->prec) || (flag->prec >= len && flag->prec > flag->width))
		{
			if (str[0] == '-' && (flag->width > -1 || flag->prec > -1))
				total++;
			else if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
				total++;
		}
		if (ft_strcmp(str, "0") == 0 && flag->prec == 0 && flag->width == -1)
			total--;
		if (flag->plus == '+' && flag->minus == '-')
			total++;
		else if (flag->plus == '+' && flag->width > flag->prec && flag->width > len)
			total++;
	}
	return (total);
}

static void	ft_cpy_to_temp_digit(char **temp, char *str, t_flag *flag, int i)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == '-')
		len--;
	if (flag->minus != '-')
		i -= len;
	if (flag->prec == 0 && ft_strcmp(str, "0") == 0)
	{
		if (spec_check(flag, 'o', 'x', 'X') == TRUE && flag->hash == TRUE)
			(*temp)[i] = '0';
		else
			(*temp)[i] = ' ';
	}
	else if (str[0] == '-')
		ft_strcpy(&(*temp)[i], &str[1]);
	else
		ft_strcpy(&(*temp)[i], str);
}

/*
**	calculate the amount of space we need to consider when printing digits
**	narrows down what extra needs to be printed to have correct width
*/

static void	ft_minus_decide_strcpy(char *str, t_flag *flag, int total, int len)
{
	int	i;
	int	new_total;

	if (flag->minus == '1')
		ft_cpy_to_temp_digit(&flag->str, str, flag, total);
	else
	{
		i = 0;
		new_total = ft_check_flags_digit(str, flag, total, len);
		if (spec_check(flag, 'n', 'x', 'X') == TRUE && flag->hash == TRUE)
			i += 2;
		else if (flag->spec == 'o' && flag->hash == TRUE)
			i++;
		if (flag->prec > len && flag->hash == TRUE && flag->spec == 'o')
			i += flag->prec - len - 1;
		else if (flag->prec > len)
			i += flag->prec - len;
		if (total < new_total)
			i++;
		ft_cpy_to_temp_digit(&flag->str, str, flag, i);
		while (i < total)
		{
			if (flag->str[i] == '\0')
				flag->str[i] = ' ';
			i++;
		}
	}
}

void	ft_digit_print(char *str, t_flag *flag, int len, int total)
{
	if (spec_check(flag, 'd', 'u', 'f') == TRUE || spec_check(flag, 'n', 'x', 'X') == TRUE)
		if (flag->prec == 0 && ft_strcmp(str, "0") == 0 && flag->width == -1)
			return ;
	flag->str = ft_strnew(total);
	if (!flag->str)
		return (ft_putstr_fd("error\n", 2));
	//if (spec_check(flag, 'd', 'u', 'f') == TRUE)
	ft_set_base_str(str, flag, total, len);
	//else
	//	ft_set_base_str_ox(str, flag, total, len);
	if (!(flag->spec != 'u' && ft_strcmp(str, "0") == 0 && ft_strlen(str) == 0 && flag->prec == 0))
		ft_minus_decide_strcpy(str, flag, total, len);
	flag->ret += write(1, flag->str, total);
	ft_strdel(&str);
	ft_strdel(&flag->str);
}
// unsigned int behaves a bit wierd with the length of printing but it says it prints the correct?
//unsgined int is wierd when minus == '-' && width > prec && prec != -1
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
	if (flag->minus == '-')
		flag->zero = '1';
	if (*format == 'd' || *format == 'i')
	{
		nbr = va_arg(*arg, long long);
		str = ft_convert_length(str, flag, nbr);
		flag->spec = 'd';
		ft_print_calc(str, flag, &ft_digit_print);
	}
	else if (*format == 'u')
	{
		var = va_arg(*arg, unsigned long long);
		str = ft_convert_length_u(str, flag, var);
		flag->spec = 'u';
		ft_print_calc(str, flag, &ft_digit_print);
	}
}
