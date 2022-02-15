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
	flag->index = 0;
	flag->flags = FALSE;
}

static char	ft_hex_digit(int value)
{
	if (value >= 0 && value < 10)
		return ('0' + value);
	else
		return ('a' + value - 10);
}

static void	ft_hex_to_str(void* addr, char *str)
{/*
	int	i;
	int count;
	uintptr_t	pnt;
	
	pnt = (uintptr_t)addr;
	i = (sizeof(pnt) << 3) - 4;
	count = 2;
	while (i >= 0)
	{
		str[count++] = ft_hex_digit((pnt >> i) & 0xf);
		i -= 4;
	}*/
	int	i;
	int count;
	uintptr_t	pnt;
	
	pnt = (uintptr_t)addr;
	i = (sizeof(pnt) << 3) - 4;
	count = 2;
	while (i >= 0)
	{
		str[count++] = ft_hex_digit((pnt >> i) & 0xf);
		i -= 4;
	}
	/*
	size_t printed = 0;
	size_t i;
	const unsigned char* pnt = addr;

	i = 0;
	while (++i < size)
	{
		int g;
		g = (*(pnt + i) >> 4) & 0xf;
		if (g >= 10)
			g += 'a' - 10;
		else
			g += '0';
		*str++ = g;
		printed++;

		g = *(pnt + i) & 0xf;
		if (g >= 10)
			g += 'a' - 10;
		else
			g += '0';
		*str++ = g;
		printed++;
	}*/
}

static void	ft_cspf_print(const char *format, char *str, t_flag *flag, va_list *arg)
{
	char * str_arg;
	int	i;

	i = 0;
	if (*format == 'c')
		*str = (char)va_arg(*arg, int);
	else if (*format == 's')
	{
		str_arg = va_arg(*arg, char*);
		ft_strcpy(str, str_arg);
		flag->index += ft_strlen(str_arg) - 1;
	}
	else if (*format == 'p')
	{
		str_arg = va_arg(*arg, char*);
		str[0] = '0';
		str[1] = 'x';
		ft_hex_to_str(str_arg, str);
		flag->index += 13;
	}
	else
	{
		//f
	}
}
/*
static void	ft_diu_print(const char *format, char *str, t_flag *flag, va_list *arg)
{
	char temp[20];

	if (*format == 'd')
	{
		ft_itoa_base(va_arg(*arg, int), temp, 10);
		ft_putstr(temp);
		ft_strcpy(str, temp);
		flag->index = ft_strlen(temp);
	}
	else if (*format == 'i')
	{
		
	}
	else if (*format == 'u')
	{
		
	}
}*/

static int	ft_convert_symbol(const char *format, char *str, t_flag *flag, va_list *arg)
{
	if (*format == 'c' || *format == 's' || *format == 'p' || *format == 'f')
	{
		ft_cspf_print(format, str, flag, arg);
		return (TRUE);
	}
	else if (*format == 'd' || *format == 'i' || *format == 'u')
	{
		//ft_diu_print(format, str, flag, arg);
		return (TRUE);
	}
	else if (*format == 'o' || *format == 'x' || *format == 'X')
	{
		//ft_oxX_print(format, str, flag, arg);
		return (TRUE);
	}
	return (FALSE);
}

static void	ft_find_flags(const char *format, char *str, t_flag *flag, va_list *arg)
{
	int	i;
	//char * str_arg;

	i = 0;
	if (ft_convert_symbol(&format[i], &str[i], flag, arg) == TRUE)
		return ;
	else
	{
		flag->flags = TRUE;
		/*if (*format == '#')
		str_arg = va_arg(*arg, char*);
		ft_strcpy(str, str_arg);
		flag->index += ft_strlen(str_arg) - 1;*/
	}
}

static void	ft_convert_checker(const char *format, char *str, t_flag *flag, va_list *arg)
{
	
	ft_find_flags(format, str, flag, arg);
	if (flag->flags == FALSE)
		return ;
	//ft_str_convert(str, flag);
}

//write char imidiately or store in a string
//exactly how to use va_start etc... and why is it good to use

int	ft_printf(const char *format, ...)
{
	int		i;
	char	str[100];
	va_list	arg;
	t_flag	*flag;

	flag = (t_flag *) malloc(sizeof(t_flag));
	if (!flag)
		ft_putstr("error");
	ft_initialize_flag(flag);
	va_start(arg, format);
	i = 0;
	//str = ft_strnew(ft_strlen(format));
	if (format)
	{
		while (format[i] != '\0')
		{
			if (format[i] != '%')
				str[flag->index] = format[i];
			else
			{
				i++;
				if (format[i] == '%')
					str[flag->index] = '%';
				else
					ft_convert_checker(&format[i], &str[flag->index], flag, &arg);
			}
			i++;
			flag->index++;
		}
	}
	str[flag->index] = '\0';
	ft_putstr(str);
	va_end(arg);
	return (ft_strlen(str)); 
	//return (0);
}


//stuck on trying to make it get the string from va_argv