/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:00:37 by molesen           #+#    #+#             */
/*   Updated: 2022/02/22 13:00:39 by molesen          ###   ########.fr       */
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

static void	ft_i_reset(const char *format, t_flag *flag)
{
	int		i;

	i = 0;
	while (format[i - 1] != '%')
		i--;
	i *= -1;
	flag->i += i;
}
static void	ft_c_flag_calc(const char *format, char *str, t_flag *flag, int c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if (flag->width > 1)
	{
		if (flag->minus == TRUE)
		{
			i = ft_strlen(str);
			ft_putchar(*str);
			while (i++ < flag->width)
				ft_putchar(' ');
			i += - 2;
		}
		else
		{
			while (i++ < (flag->width - len))
				ft_putchar(' ');
			if (c == 'c')
				ft_putchar(*str);
			else
				ft_putstr(str);
			i += len - 2;
		}
		flag->len += i;
	}
	else
	{
		if (c == 'c')
			ft_putchar(*str);
		else
			ft_putstr(str);
	}
	ft_i_reset(format, flag);
}

static void	ft_csp_print(const char *format, t_flag *flag, va_list *arg)
{
	char * str_arg;
	char	c;
	unsigned long long	long_arg;
	int		i;

	i = 0;
	if (*format == 'c')
	{
		c = (char)va_arg(*arg, int);
		if (flag->flags == TRUE)
			ft_c_flag_calc(format, &c, flag, 'c');
		else
			ft_putchar(c);
	}
	else if (*format == 's')
	{
		/*
		**need to make this work with the flag of width
		*/
		str_arg = va_arg(*arg, char*);
		if (flag->flags == TRUE)
			ft_c_flag_calc(format, str_arg, flag, 's');
		else
		{
			ft_putstr(str_arg);
			flag->len += ft_strlen(str_arg) - 1;
		}
	}
	else if (*format == 'p')
	{
		/*
		**need to make this work with the flag of width
		*/
		long_arg = va_arg(*arg, unsigned long long);
		//if (flag->flags == TRUE)
			//ft_c_flag_calc(format, long_arg, flag, 'p');
		//else
		//{
			ft_hex_to_str(long_arg, 0);
			ft_pntlen(long_arg, flag);
		//}
	}
}
/*
static int	ft_pow(int x, int y)
{
	int	power;
	int	i;

	power = 1;
	i = 1;
	while (i <= y)
	{
		power *= x;
		i++;
	}
	return (power);
}

static void	ft_strrev_len(char *str, int len)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

static void	ft_check_correct_end(char *str, int len)
{
	int	i;
	int	add;
	int	dot;

	i = ft_strlen(str) - 1;
	dot = ft_strlen_stop(str, '.') + 1;
	add = 0;
	while (str[i] && (i >= (dot + len) || add == 1))
	{
		if (str[i] == '.')
			i--;
		if (add == 1)
		{
			if (str[i] == '9')
			{
				str[i] = '0';
				add = 1;
			}
			else
			{
				str[i] = str[i] + 1;
				add = 0;
			}
		}
		if (str[i] > '5' && i >= (dot + len))
		{
			str[i] = str[i] - 1;
			add = 1;
		}
		i--;
	}
}

static void	ft_itoa_add_zeros(int nbr, char *str, int len)
{
	int	i;
	int	neg;

	i = 0;
	neg = 1;
	if (nbr < 0)
	{
		neg = -1;
		nbr *= neg;
	}
	else if (nbr == 0 && len == 0)
		str[i++] = '0';
	while (nbr)
	{
		str[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	while (i < len)
		str[i++] =  '0';
	if (neg == -1)
		str[i++] = '-';
	ft_strrev_len(str, i);
	str[i] = '\0';
}

static void	ft_float_itoa(double number, char *str, int len)
{
	long double	lnbr;
	int			nbr;
	int			i;
	char		temp[100];

	nbr = (int)number;
	lnbr = number - (long double)nbr;
	ft_itoa_add_zeros(nbr, temp, 0);
	i = ft_strlen(temp);
	if (len != 0)
	{
		if (lnbr < 0)
			lnbr *= -1;
		temp[i++] = '.';
		lnbr = lnbr * ft_pow(10, 9);
		ft_itoa_add_zeros((int)lnbr, &temp[i], 9);
		ft_check_correct_end(temp, len);
	}
	ft_strncpy(str, temp, i + len);
}

static void	ft_diuf_print(const char *format, char *str, t_flag *flag, va_list *arg)
{
	int	nbr;
	unsigned int	var;
	double	number;

	if (*format == 'd' || *format == 'i')
	{
		nbr = va_arg(*arg, int);
		ft_itoa_base(nbr, str, 10);
		flag->index += ft_strlen(str) - 1;
	}
	else if (*format == 'u')
	{
		var	 = va_arg(*arg, unsigned int);
		if ((int)var < 0)
		{
			// return error if unsigned int isn't positive?
			var = (int)var * -1;
		}
		ft_itoa_base(var, str, 10);
		flag->index += ft_strlen(str) - 1;
	}
	else if (*format == 'f')
	{
		number = va_arg(*arg, double);
		if (flag->prec != FALSE)
			ft_float_itoa(number, str, flag->prec);
		else
			ft_float_itoa(number, str, 6);
		flag->index += ft_strlen(str) - 1;
	}
	//make sure to round up / down the number depending on len i have provided...
}

static void	ft_oxX_print(const char *format, char *str, t_flag *flag, va_list *arg)
{
	int	nbr;

	nbr = va_arg(*arg, int);
	if (*format == 'o' && flag->flags == FALSE)
	{
		ft_itoa_base(nbr, str, 8);
		flag->index += ft_strlen(str) - 1;
	}
	else if (*format == 'x' && flag->flags == FALSE)
	{
		ft_itoa_base(nbr, str, 16);
		flag->index += ft_strlen(str) - 1;
		while (*str)
		{
			if (*str >= 'A' && *str <= 'Z')
				*str = ft_tolower(*str);
			str++;
		}
	}
	else if (*format == 'X' && flag->flags == FALSE)
	{
		ft_itoa_base(nbr, str, 16);
		flag->index += ft_strlen(str) - 1;
		while (*str)
		{
			if (*str >= 'a' && *str <= 'z')
				*str = ft_toupper(*str);
			str++;
		}
	}
	//if minus - problem with octal or doesn't return properly with the \0
}
*/
int	ft_convert_symbol(const char *format, t_flag *flag, va_list *arg)
{
	if (*format == 'c' || *format == 's' || *format == 'p')
	{
		ft_csp_print(format, flag, arg);
		return (TRUE);
	}/*
	else if (*format == 'd' || *format == 'i' || *format == 'u' || *format == 'f')
	{
		ft_diuf_print(format, flag, arg);
		return (TRUE);
	}
	else if (*format == 'o' || *format == 'x' || *format == 'X')
	{
		ft_oxX_print(format, flag, arg);
		return (TRUE);
	}*/
	return (FALSE);
}

//di difference - has to figure out if there is one
//oxX - still errors when it comes to minus values and x doesn't always print lower characters
