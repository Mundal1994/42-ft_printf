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

static void	ft_pntlen(uintptr_t addr, t_flag *flag)
{
	int	len;

	len = 0;
	if (addr == 0)
		flag->len += 3;
	while (addr != 0)
	{
		len++;
		addr = addr / 16;
	}
	flag->len += len + 1;
}

static void	ft_hex_to_str(uintptr_t addr, int i)
{
	if (i == 0)
		ft_putstr("0x");
	if (addr >= 16)
	{
		ft_hex_to_str(addr / 16, 1);
		ft_hex_to_str(addr % 16, 1);
	}
	else
	{
		if (addr <= 9)
			ft_putchar(addr + '0');
		else
			ft_putchar(addr - 10 + 'a');
	}
}

static void	ft_space_zero_calc(t_flag *flag, int len)
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

static void	ft_prec_calc(char *str, t_flag *flag)
{
	int	i;

	i = 0;
	if (flag->prec == -1)
	{
		if (flag->spec == 'c')
			ft_putchar(*str);
		else
		{
			ft_putstr(str);
			flag->len += ft_strlen(str) - 1;
		}
	}
	else
	{
		if (flag->spec == 'c')
			ft_putchar(*str);
		else
		{
			while (i < flag->prec && str[i] != '\0')
				ft_putchar(str[i++]);
			if (flag->width >= 0 && flag->prec < flag->width)
				flag->len += flag->width - 1;
			else
				flag->len += flag->prec - 1;
		}
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
		ft_print_calc(str, flag, &ft_prec_calc, &ft_space_zero_calc);
	}
	else if (*format == 's')
	{
		str_arg = va_arg(*arg, char*);
		flag->spec = 's';
		str = ft_str_creater(str_arg, flag->spec);
		ft_print_calc(str, flag, &ft_prec_calc, &ft_space_zero_calc);
	}
	else if (*format == 'p')
	{
		long_arg = va_arg(*arg, unsigned long long);
		flag->spec = 'p';
		ft_hex_to_str(long_arg, 0);
		ft_pntlen(long_arg, flag);
	}
}
