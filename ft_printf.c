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

static void	ft_pntlen(uintptr_t addr, t_flag *flag)
{
	int	len;

	len = 0;
	if (addr == 0)
		flag->index += 3;
	while (addr != 0)
	{
		len++;
		addr = addr / 16;
	}
	flag->index += len + 1;
}

static void	ft_hex_to_str(uintptr_t addr, char *str, int i)
{
	int	index;

	if (i == 0)
	{
		str[0] = '0';
		str[1] = 'x';
	}
	if (addr >= 16)
	{
		ft_hex_to_str(addr / 16, str, 1);
		ft_hex_to_str(addr % 16, str, 1);
	}
	else
	{
		index = ft_strlen(str);
		if (addr <= 9)
			str[index] = addr + '0';
		else
			str[index] = addr - 10 + 'a';
	}
}

static void	ft_cspf_print(const char *format, char *str, t_flag *flag, va_list *arg)
{
	char * str_arg;
	unsigned long long	long_arg;
	int	i;

	i = 0;
	if (*format == 'c' && flag->flags == FALSE)
		*str = (char)va_arg(*arg, int);
	else if (*format == 's' && flag->flags == FALSE)
	{
		str_arg = va_arg(*arg, char*);
		ft_strcpy(str, str_arg);
		flag->index += ft_strlen(str_arg) - 1;
	}
	else if (*format == 'p' && flag->flags == FALSE)
	{
		long_arg = va_arg(*arg, unsigned long long);
		ft_hex_to_str(long_arg, str, 0);
		ft_pntlen(long_arg, flag);
	}
	else if (*format == 'f')
	{
		//f
	}
}

static void	ft_diu_print(const char *format, char *str, t_flag *flag, va_list *arg)
{
	int	nbr;

	if (*format == 'd')
	{
		nbr = va_arg(*arg, int);
		ft_itoa_base(nbr, str, 10);
		flag->index += ft_strlen(str) - 1;
	}
	else if (*format == 'i')
	{
		nbr = va_arg(*arg, int);

		// it doesn't recognize the octal because nbr doesnt keep the 0
		/*if (nbr >= 0 && ft_isxdigit(nbr) == 1)
		{
			ft_itoa_base(nbr, str, 16);
			ft_putstr("hex");
		}
		else if (nbr >= 0 && ft_isoctal(nbr) == 1)
		{
			ft_putstr("octal");
			ft_itoa_base(nbr, str, 8);
		}
		else
		{*/
			//ft_putstr("decimal");
			ft_itoa_base(nbr, str, 10);
		//}
		flag->index += ft_strlen(str) - 1;
	}
	else if (*format == 'u')
	{
		
	}
}

static void	ft_oxX_print(const char *format, char *str, t_flag *flag, va_list *arg)
{
	int	nbr;

	nbr = va_arg(*arg, int);
	if (*format == 'o' && flag->flags == FALSE)
	{
		ft_itoa_base(nbr, str, 8);
		flag->index += ft_strlen(str) - 1;
	}
	else if (*format == 'x' && flag->flags == FALSE)
	{
		ft_itoa_base(nbr, str, 16);
		flag->index += ft_strlen(str) - 1;
	}
	else if (*format == 'X' && flag->flags == FALSE)
	{
		ft_itoa_base(nbr, str, 16);
		flag->index += ft_strlen(str) - 1;
	}
	//if minus - problem with octal or doesn't return properly with the \0
}

//di difference - has to figure out if there is one
//oxX - still errors when it comes to minus values and x doesn't always print lower characters

static int	ft_convert_symbol(const char *format, char *str, t_flag *flag, va_list *arg)
{
	if (*format == 'c' || *format == 's' || *format == 'p' || *format == 'f')
	{
		ft_cspf_print(format, str, flag, arg);
		return (TRUE);
	}
	else if (*format == 'd' || *format == 'i' || *format == 'u')
	{
		ft_diu_print(format, str, flag, arg);
		return (TRUE);
	}
	else if (*format == 'o' || *format == 'x' || *format == 'X')
	{
		ft_oxX_print(format, str, flag, arg);
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
	ft_bzero(str, 100);
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
}


//stuck on trying to make it get the string from va_argv