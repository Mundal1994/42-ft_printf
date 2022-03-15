/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:47:11 by molesen           #+#    #+#             */
/*   Updated: 2022/03/01 12:47:13 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_space_calc_csp(t_flag *flag, int len)
{
	if (flag->plus == TRUE)
		len++;
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

static char	*ft_str_creater(char *str_arg, char c)
{
	char *str;

	if (c == 'c')
	{
		str = ft_strnew(1);
		ft_strncpy(str, str_arg, 1);
	}
	else
	{
		if (!str_arg)
		{
			str = ft_strnew(ft_strlen("(null)"));
			ft_strcpy(str, "(null)");
		}
		else
		{
			str = ft_strnew(ft_strlen(str_arg));
			ft_strcpy(str, str_arg);
		}
	}
	return (str);
}

static char	*ft_address_to_str(uintptr_t addr)
{
	char	*str;
	char	*dest;

	dest = ft_strnew(14);
	str = ft_strnew(12);
	if (!str && !dest)
		return (NULL);
	str = ft_htoa(str, addr);
	ft_strcpy(dest, "0x");
	ft_strcpy(&dest[2], str);
	ft_strdel(&str);
	return (dest);
}

void	ft_csp_print(const char *format, t_flag *flag, va_list *arg)
{
	char * str_arg;
	char	c;
	unsigned long long	long_arg;
	char	*str;

	if (*format == 'c')
	{
		c = (char)va_arg(*arg, int);
		flag->spec = 'c';
		str = ft_str_creater(&c, flag->spec);
		ft_print_calc(str, flag, &ft_space_calc_csp);
	}
	else if (*format == 's')
	{
		str_arg = va_arg(*arg, char*);
		flag->spec = 's';
		str = ft_str_creater(str_arg, flag->spec);
		ft_print_calc(str, flag, &ft_space_calc_csp);
	}
	else if (*format == 'p')
	{
		long_arg = va_arg(*arg, unsigned long long);
		str = ft_address_to_str(long_arg);
		ft_print_calc(str, flag, &ft_space_calc_csp);
	}
}
//if strnew fails th en what happens?