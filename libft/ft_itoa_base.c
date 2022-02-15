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

static void	ft_itoa_helper(char *str, int nbr, int base)
{
	int digit;

	digit = 0;
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
}

char	*ft_itoa_base(int nbr, char *strout, int base)
{
	char *str;
	int	neg;

	str = strout;
	neg = 0;
	if (nbr < 0)
	{
		neg = -1;
		nbr *= neg;
	}
	ft_itoa_helper(str, nbr, base);
	if (neg == -1)
		*str++ = '-';
	*str = '\0';
	ft_strrev(strout);
	return (strout);
}
