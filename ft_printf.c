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

void	ft_i_reset(const char *format, t_flag *flag)
{
	int		i;

	i = 0;
	while (format[i - 1] != '%')
		i--;
	i *= -1;
	flag->i += i;
}

static void	ft_initialize_flag(t_flag *flag, int first)
{
	flag->spec = '0';
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

static void	ft_check_char(const char *format, t_flag *flag, va_list *arg)
{
	if (format[flag->i] != '%')
	{
		if (format[flag->i] == '{')
		{
			flag->i++;
			if (format[flag->i] == '{')
				ft_putchar('{');
			else if (ft_color_print(&format[flag->i], flag) == FALSE)
				ft_putchar(format[--flag->i]);
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
			ft_flag_checker(&format[flag->i], flag, arg);
			ft_initialize_flag(flag, FALSE);
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	t_flag	*flag;

	flag = (t_flag *) malloc(sizeof(t_flag));
	if (!flag)
		ft_putstr("error\n");
	ft_initialize_flag(flag, TRUE);
	va_start(arg, format);
	if (format)
	{
		while (format[flag->i] != '\0')
		{
			ft_check_char(format, flag, &arg);
			flag->i++;
			flag->len++;
		}
	}
	va_end(arg);
	free(flag);
	return (flag->len); 
}

//can work on error handling ex if someone writes something incorreeclty with %kf;ls,
//ask jeff:
// pointers do they do anything with any of the flags if you do %p?