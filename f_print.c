/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 09:36:03 by molesen           #+#    #+#             */
/*   Updated: 2022/03/15 09:36:31 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void	ft_f_print(const char *format, t_flag *flag, va_list *arg)
{
	double				number;
	long double			b_number;
	char				*str;

	str = NULL;
	if (*format == 'f')
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
		ft_print_calc(str, flag, &ft_space_calc_digit);
	}
	else
		ft_b_print(format, flag, arg);
	//make sure to round up / down the number depending on len i have provided...
}
