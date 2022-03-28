/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:23:17 by molesen           #+#    #+#             */
/*   Updated: 2022/03/28 11:23:19 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	error when creating string	*/

void	ft_str_error(char *str, t_flag *flag)
{
	if (str)
		ft_strdel(&str);
	free(flag);
	ft_putstr("\033[31m");
	ft_putstr_fd("error\n", 2);
	ft_putstr("\033[39m");
	exit(1);
}

/*	error anywhere else	*/

void	ft_error(char *str, t_flag *flag)
{
	ft_putstr("\033[31m");
	ft_putstr_fd(str, 2);
	ft_putstr("\033[39m");
	if (flag)
		free(flag);
	exit(1);
}
