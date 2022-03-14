/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:28:12 by molesen           #+#    #+#             */
/*   Updated: 2022/02/21 13:28:27 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_initialize_flag(t_flag *flag, int first)
{
	flag->flags = FALSE;
	flag->hash = FALSE;
	flag->space = FALSE;
	flag->minus = FALSE;
	flag->plus = FALSE;
	flag->zero = FALSE;
	flag->width = -1;
	flag->prec = -1;
	flag->hh = FALSE;
	flag->h = FALSE;
	flag->l = FALSE;
	flag->ll = FALSE;
	flag->s_l = FALSE;
	flag->b_l = FALSE;
	if (first == TRUE)
	{
		flag->i = 0;
		flag->len = 0;
	}
}

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

static int	ft_color_print(const char *str, t_flag *flag)
{
	int	len;

	len = ft_strlen_stop((char *)&str[1], '}');
	if (ft_color_check(str, len) == FALSE)
		return (FALSE);
	flag->i += len + 1;
	return (TRUE);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	t_flag	*flag;

	flag = (t_flag *) malloc(sizeof(t_flag));
	if (!flag)
		ft_putstr("error");
	ft_initialize_flag(flag, TRUE);
	va_start(arg, format);
	if (format)
	{
		while (format[flag->i] != '\0')
		{
			if (format[flag->i] != '%')
			{
				if (format[flag->i] == '{')
				{
					if (ft_color_print(&format[flag->i], flag) == FALSE)
						ft_putchar(format[flag->i]);
				}
				else
					ft_putchar(format[flag->i]);
			}
			else
			{
				flag->i++;
				if (format[flag->i] == '%')
					ft_putchar('%');
				else
				{
					ft_convert_checker(&format[flag->i], flag, &arg);
					ft_initialize_flag(flag, FALSE);
				}
			}
			flag->i++;
			flag->len++;
		}
	}
	va_end(arg);
	free(flag);
	return (flag->len); 
}
