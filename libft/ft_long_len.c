/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:40:41 by molesen           #+#    #+#             */
/*   Updated: 2022/03/08 15:41:24 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_long_min(long long i)
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

static int	ft_len_long_max(long long i)
{
	if (i >= 1000000000000000000)
		return (19);
	if (i >= 100000000000000000)
		return (18);
	if (i >= 10000000000000000)
		return (17);
	if (i >= 1000000000000000)
		return (16);
	if (i >= 100000000000000)
		return (15);
	if (i >= 10000000000000)
		return (14);
	if (i >= 1000000000000)
		return (13);
	if (i >= 100000000000)
		return (12);
	return (11);
}

int	ft_long_len(long long nbr)
{
	if (nbr < 0)
	{
		if (nbr == -9223372036854775807)
			return (20);
		else
		{
			nbr *= -1;
			if (nbr >= 10000000000)
				return (ft_len_long_max(nbr) + 1);
			return (ft_len_long_min(nbr) + 1);
		}
	}
	if (nbr >= 10000000000)
		return (ft_len_long_max(nbr));
	return (ft_len_long_min(nbr));
}
