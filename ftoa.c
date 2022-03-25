/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:59:43 by molesen           #+#    #+#             */
/*   Updated: 2022/03/15 16:59:56 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_correct_end_loop(char *str, int total, int add, int *i)
{
	while (str[*i] && (*i >= total || add == 1))
	{
		if (str[*i] == '.')
			*i -= 1;
		if (add == 1)
		{
			if (str[*i] == '9')
			{
				str[*i] = '0';
				add = 1;
			}
			else
			{
				str[*i] = str[*i] + 1;
				add = 0;
			}
		}
		if (str[*i] >= '5' && *i >= total)
		{
			str[*i] = str[*i] - 1;
			add = 1;
		}
		*i -= 1;
	}
	return (add);
}

static void	ft_check_correct_end(char *str, int len, int dot)
{
	int		i;
	int		total;
	int		add;
	char	*temp;

	i = dot + len;
	total = dot + len;
	add = 0;
	if (ft_strncmp(&str[dot - 1], ".25", len + 2) == 0 && len == 1)
		str[dot] = '2';
	else
		add = ft_correct_end_loop(str, total, 0, &i);
	if (add == 1)
	{
		temp = ft_strnew(ft_strlen(str));
		ft_strcpy(temp, str);
		ft_strdel(&str);
		str = ft_strnew(ft_strlen(temp) + 1);
		str[0] = '1';
		ft_strcpy(&str[1], temp);
		ft_strdel(&temp);
	}
}

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

static double	ft_fcalc(double number, char *temp, double lnbr)
{
	long long	nbr;
	int			neg;

	if ((int)number == 0)
	{
		temp[0] = '0';
		return (lnbr);
	}
	neg = 1;
	nbr = (long long)number;
	lnbr -= (double)nbr;
	if (nbr < 0)
	{
		neg = -1;
		nbr *= neg;
	}
	ft_itoa_add_zeros((unsigned long long)nbr, temp, 0, neg);
	return (lnbr);
}

char	*ft_ftoa(double number, int len)
{
	double	lnbr;
	int		i;
	char	*temp;
	char	*str;
	int		dot;

	lnbr = number;
	temp = NULL;
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
		dot = ft_strlen_stop(temp, '.') + 1;
		ft_check_correct_end(temp, len, dot);
	}
	str = ft_strnew(i + len);
	ft_strncpy(str, temp, i + len);
	ft_strdel(&temp);
	return (str);
}
