/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:47:11 by molesen           #+#    #+#             */
/*   Updated: 2022/03/01 12:47:13 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	helper function for ft_str_print	*/

static void	ft_print_depend_on_char(char *str, t_flag *flag, int total, char c)
{
	flag->str = ft_strnew(total);
	if (!flag->str)
	{
		ft_str_error(str, flag);
		return ;
	}
	if (flag->spec == 'p' && ft_strcmp(str, "0x0") == 0 && flag->prec > 0)
		ft_memset(flag->str, '0', total);
	else
		ft_memset(flag->str, ' ', total);
	if (flag->minus == '1' && flag->spec != 'c')
		ft_cpy_to_temp_str(&flag->str, str, flag, total);
	else if (flag->spec != 'c')
		ft_cpy_to_temp_str(&flag->str, str, flag, 0);
	if (flag->spec == 'c' && flag->minus == '-')
		flag->ret += write(1, &c, 1);
	flag->ret += write(1, flag->str, total);
	if (flag->spec == 'c' && flag->minus == '1')
		flag->ret += write(1, &c, 1);
	ft_strdel(&str);
	ft_strdel(&flag->str);
}

/*	calculations of printing the string	*/

static void	ft_str_print(char *str, t_flag *flag, int total, va_list *arg)
{
	int	c;

	if (flag->spec == 'c')
	{
		c = (char)va_arg(*arg, int);
		if (!(flag->width < 0))
			total--;
		if (flag->width == 0)
		{
			flag->ret += write(1, &c, 1);
			return ;
		}
	}
	if (flag->width == 0 && flag->spec != 'c')
		return ;
	if (flag->spec == 'p' && ft_strncmp(str, "0x0", 3) == 0 && flag->prec > 0)
	{
		total = flag->prec + 2;
		flag->prec += 2;
	}
	ft_print_depend_on_char(str, flag, total, c);
}

/*	createed string from arg depending on specifier	*/

static char	*ft_str_creater(char *str_arg, char c)
{
	char	*str;

	if (c == 'c')
		str = ft_strnew(1);
	else if (!str_arg)
		str = ft_strnew(ft_strlen("(null)"));
	else
		str = ft_strnew(ft_strlen(str_arg));
	if (!str)
		return (NULL);
	if (c == 'c')
		ft_strncpy(str, "\0", 1);
	else if (!str_arg)
		ft_strcpy(str, "(null)");
	else
		ft_strcpy(str, str_arg);
	return (str);
}

/*	calls function that will calculate string	*/

static void	ft_print_str(char *str, t_flag *flag, va_list *arg)
{
	if (!str && flag->spec != 'c')
	{
		ft_str_error(str, flag);
		return ;
	}
	ft_print_calc(str, flag, &ft_str_print, arg);
}

/*	narrows down specifier and get arg	*/

void	ft_csp_print(const char *format, t_flag *flag, va_list *arg)
{
	char	*str;

	str = NULL;
	flag->zero = '1';
	if (*format == 'c')
	{
		flag->spec = 'c';
		str = ft_str_creater(" ", flag->spec);
	}
	else if (*format == 's')
	{
		flag->spec = 's';
		str = ft_str_creater((char *)va_arg(*arg, char *), flag->spec);
	}
	else if (*format == 'p')
	{
		flag->spec = 'p';
		str = addr_to_str((unsigned long long)va_arg(*arg, unsigned long long), flag->prec);
	}
	ft_print_str(str, flag, arg);
}
