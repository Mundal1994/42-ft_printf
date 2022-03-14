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

static void	ft_space_zero_calc(t_flag *flag, int len)
{
	if ((flag->plus == TRUE || flag->space == TRUE) && flag->prec == -1 && flag->spec != 'u')
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

static void	ft_prec_calc(char *str, t_flag *flag)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (str[0] == '0' && flag->prec != -1)
		str_len = 0;
	if (flag->plus == TRUE || (flag->space == TRUE && flag->minus == TRUE))
		ft_plus_print(flag, str_len);
	if (flag->prec == -1)
	{
		ft_putstr(str);
		flag->len += str_len - 1;
	}
	else
	{
		if (flag->prec > str_len)
			ft_space_zero_calc(flag, str_len);
		if (str_len == 0)
			ft_putchar(' ');
		else
			ft_putstr(str);
		if (flag->width >= 0 && flag->prec < flag->width && flag->width > str_len)
			flag->len += flag->width - 1;
		else if (flag->prec <= str_len)
			flag->len += str_len - 1;
		else
			flag->len += flag->prec - 1;
	}
}

static unsigned long long	ft_pow(unsigned long long x, int y)
{
	unsigned long long	power;
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
/*
static double	ft_dpow(double x, int y)
{
	double	power;
	int	i;

	power = 1;
	i = 1;
	while (i <= y)
	{
		power *= x;
		i++;
	}
	return (power);
}*/

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

	dot = ft_strlen_stop(str, '.') + 1;
	i = dot + len;
	add = 0;
	if (ft_strncmp(&str[dot - 1], ".25", len + 2) == 0 && len == 1)
		str[dot] = '2';
	else
	{
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
			if (str[i] >= '5' && i >= (dot + len))
			{
				str[i] = str[i] - 1;
				add = 1;
			}
			i--;
		}
	}
}
/*
static void	ft_itoa_add_zeros(long nbr, char *str, int len)
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
*/

static void	ft_itoa_add_zeros(unsigned long long nbr, char *str, int len, int neg)
{
	int	i;

	i = 0;
	if (nbr == 0 && len == 0)
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

static long	ft_flong_len(double nbr)
{
	long	counter;

	counter = 0;
	if (nbr == 0)
		return (1);
	while (nbr >= 1)
	{
		nbr /= 10;
		counter++;
	}
	return (counter);
}

static double	ft_fcalc(double number, char *temp, double lnbr)
{
	long long	nbr;
	char		*collect;
	int			neg;

	if ((int)number == 0)
	{
		temp[0] = '0';
		return (lnbr);
	}
	collect = ft_strnew(ft_flong_len(number));
	while (lnbr >= 1 || lnbr <= -1)
	{
		neg = 1;
		nbr = (long long)number;
		lnbr -= (double)nbr;
		if (nbr < 0)
		{
			neg = -1;
			nbr *= neg;
		}
		if (number < 9223372036854775807 && number >= -9223372036854775807)
		{
			ft_itoa_add_zeros((unsigned long long)nbr, collect, 0, neg);
			ft_strcat(temp, collect);
		}
		//else
		//{
			/*
			int i = ft_flong_len(number) - 1;
			current = 0;
			int j = 0;
			double temtem = 0;
			orig = number;
			minus = 0;
			while (i >= 0)
			{
				tem = orig / ft_dpow(10, i);
				minus = current * ft_dpow(10, j++);
				current = tem - minus;
				//temtem += minus;
				ft_itoa_add_zeros(current, collect, 0, TRUE);
				ft_strcat(temp, collect);
				ft_bzero(collect, ft_long_len(current));
				i--;
			}*/
		//}
		break ;
		ft_bzero(collect, ft_long_len(nbr));
		// need to make the loop if number is bigger than in if statement. create loop to make nbr smaller and smaller.
	}
	ft_strdel(&collect);
	return (lnbr);
}

static char	*ft_ftoa(double number, int len)
{
	double	lnbr;
	int		i;
	char	*temp;
	char	*str;

	lnbr = number;
	temp = ft_strnew(ft_flong_len(number) + 19);
	lnbr = ft_fcalc(number, temp, lnbr);
	i = ft_strlen(temp);
	if (len != 0)
	{
		if (lnbr < 0)
			lnbr *= -1;
		temp[i++] = '.';
		lnbr = lnbr * ft_pow(10, 18);
		ft_itoa_add_zeros((unsigned long long)lnbr, &temp[i], 18, 1);
		ft_check_correct_end(temp, len);
	}
	str = ft_strnew(ft_strlen(temp));
	ft_strncpy(str, temp, i + len);
	ft_strdel(&temp);
	return (str);
}
/*
static char	*ft_ftoa(double number, int len)
{
	double	lnbr;
	long		nbr;
	int			i;
	char		temp[len];
	char		*str;

	nbr = (long)number;
	lnbr = number - (double)nbr;
	ft_itoa_add_zeros(nbr, temp, 0);
	i = ft_strlen(temp);
	if (len != 0)
	{
		if (lnbr < 0)
			lnbr *= -1;
		temp[i++] = '.';
		lnbr = lnbr * ft_pow(10, 9);
		ft_itoa_add_zeros(lnbr, &temp[i], 9);
		ft_check_correct_end(temp, len);
	}
	str = ft_strnew(ft_strlen(temp));
	ft_strncpy(str, temp, i + len);
	return (str);
}*/

static char	*ft_ulltoa(unsigned long long nbr, char *str)
{
	int	i;

	i = 0;
	if (!nbr)
		str[i] = '0';
	while (nbr)
	{
		str[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	ft_strrev(str);
	return (str);
}

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

static char	*ft_convert_length_u(char *str, t_flag *flag, unsigned long long nbr)
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

static char	*ft_convert_length_f(char *str, t_flag *flag, double number, long double b_nbr)
{
	if (flag->prec != -1)
	{
		if (flag->b_l)
			str = ft_ftoa(b_nbr, flag->prec);
		else
			str = ft_ftoa((double)number, flag->prec);
	}
	else
	{
		if (flag->b_l)
			str = ft_ftoa(b_nbr, 6);
		else
			str = ft_ftoa((double)number, 6);
	}
	return (str);
}

void	ft_diuf_print(const char *format, t_flag *flag, va_list *arg)
{
	long long			nbr;
	unsigned long long	var;
	double				number;
	long double			b_number;
	char				*str;

	str = NULL;
	nbr = 0;
	if (*format == 'd' || *format == 'i')
	{
		nbr = va_arg(*arg, long long);
		str = ft_convert_length(str, flag, nbr);
		flag->spec = 'd';
		ft_print_calc(str, flag, &ft_prec_calc, &ft_space_zero_calc);
	}
	else if (*format == 'u')
	{
		var	 = va_arg(*arg, unsigned long long);
		str = ft_convert_length_u(str, flag, var);
		flag->spec = 'u';
		ft_print_calc(str, flag, &ft_prec_calc, &ft_space_zero_calc);
	}
	else if (*format == 'f')
	{
		b_number = -1;
		number = -1;
		flag->spec = 'f';
		if (flag->b_l == TRUE)
		{
			b_number = va_arg(*arg, long double);
			str = ft_convert_length_f(str, flag, number, b_number);
		}
		else
		{
			number = va_arg(*arg, double);
			str = ft_convert_length_f(str, flag, number, b_number);
		}
		ft_print_calc(str, flag, &ft_prec_calc, &ft_space_zero_calc);
	}
	//make sure to round up / down the number depending on len i have provided...
}
/*
** still some issues with the minimum size of d and i. it prinntts carbage value
*/