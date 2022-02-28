/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:24:05 by molesen           #+#    #+#             */
/*   Updated: 2022/02/28 15:24:16 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_of_int(unsigned int i)
{
	if (i >= 1000000000)
		return (10);
	if (i >= 100000000)
		return (9);
	if (i >= 10000000)
		return (8);
	if (i >= 1000000)
		return (7);
	if (i >= 100000)
		return (6);
	if (i >= 10000)
		return (5);
	if (i >= 1000)
		return (4);
	if (i >= 100)
		return (3);
	if (i >= 10)
		return (2);
	return (1);
}

int	ft_int_len(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		else
		{
			n *= -1;
			return (ft_len_of_int(n) + 1);
		}
	}
	return (ft_len_of_int(n));
}
