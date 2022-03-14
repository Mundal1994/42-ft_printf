/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:10:09 by molesen           #+#    #+#             */
/*   Updated: 2022/03/14 16:10:10 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_color_check(const char *str, int len)
{
	if (ft_strncmp(&str[1], "reset", len) == 0)
		ft_putstr("\033[0m");
	else if (ft_strncmp(&str[1], "bold", len) == 0)
		ft_putstr("\033[1m");
	else if (ft_strncmp(&str[1], "red", len) == 0)
		ft_putstr("\033[31m");
	else if (ft_strncmp(&str[1], "green", len) == 0)
		ft_putstr("\033[32m");
	else if (ft_strncmp(&str[1], "yellow", len) == 0)
		ft_putstr("\033[33m");
	else if (ft_strncmp(&str[1], "blue", len) == 0)
		ft_putstr("\033[34m");
	else if (ft_strncmp(&str[1], "purple", len) == 0)
		ft_putstr("\033[35m");
	else if (ft_strncmp(&str[1], "cyan", len) == 0)
		ft_putstr("\033[36m");
	else if (ft_strncmp(&str[1], "white", len) == 0)
		ft_putstr("\033[37m");
	else if (ft_strncmp(&str[1], "uncolor", len) == 0)
		ft_putstr("\033[39m");
	else
		return (FALSE);
	return (TRUE);
}

int	ft_color_print(const char *str, t_flag *flag)
{
	int	len;

	len = ft_strlen_stop((char *)&str[1], '}');
	if (ft_color_check(str, len) == FALSE)
		return (FALSE);
	flag->i += len + 1;
	return (TRUE);
}
