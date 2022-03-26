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

static void	ft_itoa_add_zeros(unsigned long long nbr, char *str, int len, \
int neg)
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
		str[i++] = '0';
	if (neg == -1)
		str[i++] = '-';
	ft_strrev_len(str, i);
	str[i] = '\0';
}

static void	ft_fcalc(long long number, char *temp)
{
	long	nbr;
	int		neg;

	if ((int)number == 0)
	{
		temp[0] = '0';
		return ;
	}
	neg = 1;
	nbr = (long long)number;
	if (nbr < 0)
	{
		neg = -1;
		nbr *= neg;
	}
	ft_itoa_add_zeros((double)nbr, temp, 0, neg);
}

char	*ft_ftoa(long double number, int len)
{
	long double	lnbr;
	int			i;
	int			dot;
	char		*temp;
	char		*str;

	lnbr = number;
	temp = ft_strnew(ft_flong_len(number) + 20 + 1);
	ft_fcalc(number, temp);
	lnbr = number - (long long)number;
	i = ft_strlen(temp);
	if (len != 0)
	{
		if (lnbr < 0)
			lnbr *= -1;
		temp[i++] = '.';
		lnbr = lnbr * ft_pow(10, 19);
		ft_itoa_add_zeros((unsigned long long)lnbr, &temp[i], 19, 1);
		dot = ft_strlen_stop(temp, '.') + 1;
		ft_check_correct_end(temp, len, dot);
	}
	str = ft_strnew(i + len);
	ft_strncpy(str, temp, i + len);
	ft_strdel(&temp);
	return (str);
}
