/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:25:29 by molesen           #+#    #+#             */
/*   Updated: 2022/02/28 16:26:42 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_helper(char *str, long long nbr, int base, int neg)
{
	int	digit;

	digit = 0;
	if (nbr == 0)
		*str++ = '0';
	else
	{
		while (nbr)
		{
			digit = nbr % base;
			if (digit > 9)
				*str = 'A' + digit - 10;
			else
				*str = '0' + digit;
			nbr = nbr / base;
			str++;
		}
		if (neg == -1)
			*str++ = '-';
	}
	*str = '\0';
}

char	*ft_itoa_base(long long nbr, int len, int base)
{
	char	*str;
	int		neg;

	str = ft_strnew(len);
	neg = 1;
	if (nbr < 0)
	{
		neg = -1;
		nbr *= neg;
	}
	ft_itoa_helper(str, nbr, base, neg);
	ft_strrev(str);
	return (str);
}
