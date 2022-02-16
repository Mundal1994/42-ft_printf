/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:08:25 by molesen           #+#    #+#             */
/*   Updated: 2022/02/15 11:16:40 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_helper(char *str, long var, int base, int neg)
{
	int	digit;

	digit = 0;
	if (var == 0)
		*str++ = '0';
	else
	{
		while (var)
		{
			digit = var % base;
			if (digit > 9)
				*str = 'A' + digit - 10;
			else
				*str = '0' + digit;
			var = var / base;
			str++;
		}
		if (neg == -1)
			*str++ = '-';
	}
	*str = '\0';
}

char	*ft_itoa_base(int nbr, char *strout, int base)
{
	char	*str;
	int		neg;
	long	var;

	str = strout;
	neg = 1;
	var = (long)nbr;
	if (nbr < 0)
	{
		neg = -1;
		var *= neg;
	}
	ft_itoa_helper(str, var, base, neg);
	ft_strrev(strout);
	return (strout);
}
