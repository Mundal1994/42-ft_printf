/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:29:06 by molesen           #+#    #+#             */
/*   Updated: 2022/03/14 18:29:09 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_htoa(uintptr_t addr, int i)
{
	if (i == 0)
		ft_putstr("0x");
	if (addr >= 16)
	{
		ft_htoa(addr / 16, 1);
		ft_htoa(addr % 16, 1);
	}
	else
	{
		if (addr <= 9)
			ft_putchar(addr + '0');
		else
			ft_putchar(addr - 10 + 'a');
	}
}
