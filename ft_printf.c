/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:28:12 by molesen           #+#    #+#             */
/*   Updated: 2022/02/14 16:23:13 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_initialize_flag(t_flag *flag)
{
	flag->hash = FALSE;
	flag->space = FALSE;
	flag->minus = FALSE;
	flag->plus = FALSE;
	flag->zero = FALSE;
	flag->width = FALSE;
	flag->prec = FALSE;
	flag->hh = FALSE;
	flag->h = FALSE;
	flag->l = FALSE;
	flag->ll = FALSE;
	flag->s_l = FALSE;
	flag->b_l = FALSE;
}

static int	ft_convert_symbol(const char *format, char *str, va_list *arg)
{
	if (*format == 'c' || *format == 's' || *format == 'p')
	{
		if (*format == 'c')
			*str = (char)va_arg(*arg, int);
		else if (*format == 's')
			*str = *((char *)va_arg(*arg, char *));
		//else
		//	str = (char *)va_arg(*arg, char *);
		return (TRUE);
	}
	else if (*format == 'd' || *format == 'i' || *format == 'o')
	{
		return (TRUE);
	}
	else if (*format == 'u' || *format == 'x' || *format == 'X')
	{
		return (TRUE);
	}
	else if (*format == 'f')
	{
		return (TRUE);
	}
	return (FALSE);
}

static void	ft_find_flags(const char *format, char *str, t_flag *flag, va_list *arg)
{
	int	i;

	i = 0;
	if (ft_convert_symbol(&format[i], &str[i], arg) == TRUE)
	{
		//print
		(void)flag;
	}
	else
	{
		//means we have a flag loop
	}
}

static void	ft_convert_checker(const char *format, char *str, va_list *arg)
{
	t_flag	*flag;

	//va_start(arg, str);
	flag = (t_flag *) malloc(sizeof(t_flag));
	if (!flag)
		ft_putstr("error");
	ft_initialize_flag(flag);
	ft_find_flags(format, str, flag, arg);
	//ft_str_convert(str, flag);
	//va_end(arg, str);
}

//write char imidiately or store in a string
//exactly how to use va_start etc... and why is it good to use

int	ft_printf(const char *format, ...)
{
	int		i;
	int		j;
	char	str[100];
	va_list	arg;

	va_start(arg, format);
	i = 0;
	j = 0;
	//str = ft_strnew(ft_strlen(format));
	if (format)
	{
		while (format[i] != '\0')
		{
			if (format[i] != '%')
				str[j] = format[i];
			else
			{
				i++;
				if (format[i] == '%')
					str[j] = '%';
				else
				{
					//if (format[i] == 'c')
					//	str[j] = (char)va_arg(arg, int);

					// call function to check rest char
					ft_convert_checker(&format[i], &str[j], &arg);
					ft_putchar('\n');
					ft_putstr(str);
					ft_putchar('\n');
					j += ft_strlen(&str[i]);
					
				}
			}
			//ft_putnbr(i);
			i++;
			j++;
		}
	}
	str[j] = '\0';
	ft_putstr(str);
	//return (ft_strlen(str));
	va_end(arg);
	return (0);
}


//stuck on trying to make it get the string from va_argv