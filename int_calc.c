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


static void	ft_space_zero_calc(t_flag *flag, int len, int c)
{
	if ((flag->plus == TRUE || flag->space == TRUE) && flag->prec == -1 && c != 'u')
		len++;
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

static void	ft_plus_print(t_flag *flag, int c)
{
	if (c != 'u')
	{
		if (flag->width == -1 && flag->prec == -1)
		{
			if (flag->plus == TRUE)
				ft_putchar('+');
			else
				ft_putchar(' ');
			flag->len++;
		}
		else if (flag->prec == -1)
		{
			if (flag->plus == TRUE)
				ft_putchar('+');
			else
				ft_putchar(' ');
		}
		else
		{
			if (flag->plus == TRUE)
				ft_putchar('+');
			else
				ft_putchar(' ');
			flag->len++;
		}
	}
}

static void	ft_prec_calc(char *str, t_flag *flag, int c)
{
	int	str_len;

	if (c)
		str_len = 0;
	str_len = ft_strlen(str);
	if (flag->plus == TRUE || (flag->space == TRUE && flag->minus == TRUE))
		ft_plus_print(flag, c);
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

static void	ft_d_flag_calc(const char *format, char *str, t_flag *flag, int c)
{
	int		len;

	len = ft_strlen(str);
	if (flag->prec != -1 && flag->prec > len)
		len = flag->prec;
	if (flag->space == TRUE && flag->minus == FALSE)
		ft_plus_print(flag, c);
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

static char	*ft_float_itoa(double number, int len)
{
	long double	lnbr;
	int			nbr;
	int			i;
	char		temp[100];
	char		*str;

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
	str = ft_strnew(i + len);
	ft_strncpy(str, temp, i + len);
	return (str);
}

static char	*ft_utoa(unsigned int nbr)
{
	char			*result;
	char			buf[30];
	unsigned int	i;
	unsigned int	count;

	count = 0;
	i = 0;
	if (nbr == 0)
		buf[count++] = '0';
	while (nbr)
	{
		buf[count++] = "0123456789"[nbr % 10];
		nbr /= 10;
	}
	result = ft_strnew(count);
	while (i < count)
	{
		result[i] = buf[count - i - 1];
		i++;
	}
	return (result);
}

void	ft_diuf_print(const char *format, t_flag *flag, va_list *arg)
{
	int	nbr;
	unsigned int	var;
	double	number;
	char	*str;

	str = NULL;
	if (*format == 'd' || *format == 'i')
	{
		nbr = va_arg(*arg, int);
		str = ft_itoa_base(nbr, ft_int_len(nbr), 10);
		ft_d_flag_calc(format, str, flag, 'd');
	}
	else if (*format == 'u')
	{
		var	 = va_arg(*arg, unsigned int);
		if ((int)var < 0)
		{
			// return error if unsigned int isn't positive?
			var = (int)var * -1;
		}
		str = ft_utoa(var);
		ft_d_flag_calc(format, str, flag, 'u');
	}
	else if (*format == 'f')
	{
		number = va_arg(*arg, double);
		if (flag->prec != FALSE)
			str = ft_float_itoa(number, flag->prec);
		else
			str = ft_float_itoa(number, 6);
		ft_putstr(str);
		//ft_d_flag_calc(format, str, flag, 'f');
	}
	//make sure to round up / down the number depending on len i have provided...
}
/*
void	ft_oxX_print(const char *format, t_flag *flag, va_list *arg)
{
	int	nbr;
	char	*str;

	nbr = va_arg(*arg, int);
	if (*format == 'o' && flag->flags == FALSE)
	{
		str = ft_itoa_base(nbr, ft_int_len(nbr), 8);
		ft_c_flag_calc(format, str, flag, 'd');
		//flag->index += ft_strlen(str) - 1;
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
	}*/
	//if minus - problem with octal or doesn't return properly with the \0
//}
