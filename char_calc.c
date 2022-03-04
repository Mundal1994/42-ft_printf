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

static void	ft_prec_calc(char *str, t_flag *flag, int c, int i)
{
	if (flag->prec == -1)
	{
		if (c == 'c')
			ft_putchar(*str);
		else
		{
			ft_putstr(str);
			flag->len += ft_strlen(str) - 1;
		}
	}
	else
	{
		if (c == 'c')
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

static void	ft_c_flag_calc(const char *format, char *str, t_flag *flag, int c)
{
	int		len;

	if (c == 'c')
		len = 1;
	else
	{
		len = flag->prec;
		if (flag->prec == -1)
			len = ft_strlen(str);
	}
	if (flag->width >= 0)
	{
		if (flag->width >= len && flag->prec == -1)
			flag->len += flag->width - len;
		if (flag->minus == TRUE)
		{
			ft_prec_calc(str, flag, c, 0);
			ft_space_zero_calc(flag, len);
		}
		else
		{
			ft_space_zero_calc(flag, len);
			ft_prec_calc(str, flag, c, 0);
		}
	}
	else
		ft_prec_calc(str, flag, c, 0);
	ft_i_reset(format, flag);
}

void	ft_csp_print(const char *format, t_flag *flag, va_list *arg)
{
	char * str_arg;
	char	c;
	unsigned long long	long_arg;

	if (*format == 'c')
	{
		c = (char)va_arg(*arg, int);
		ft_c_flag_calc(format, &c, flag, 'c');
	}
	else if (*format == 's')
	{
		str_arg = va_arg(*arg, char*);
		ft_c_flag_calc(format, str_arg, flag, 's');
	}
	else if (*format == 'p')
	{
		long_arg = va_arg(*arg, unsigned long long);
		ft_hex_to_str(long_arg, 0);
		ft_i_reset(format, flag);
		ft_pntlen(long_arg, flag);
	}
}
