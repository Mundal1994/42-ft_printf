/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addr_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:44:25 by molesen           #+#    #+#             */
/*   Updated: 2022/03/26 17:44:27 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*addr_to_str(uintptr_t addr)
{
	char	*str;
	char	*dest;

	dest = ft_strnew(14);
	str = ft_strnew(12);
	if (!str && !dest)
		return (NULL);
	if (addr == 0)
		ft_strcpy(str, "0");
	else
		str = ft_htoa(str, addr);
	ft_strcpy(dest, "0x");
	ft_strcpy(&dest[2], str);
	ft_strdel(&str);
	return (dest);
}
