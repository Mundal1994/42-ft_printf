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

/*	copies final content of string into main str	*/

static void	ft_cpy_to_temp_str(char **temp, char *str, t_flag *flag, int i)
{
	int	remain;

	if (flag->spec == 'p' && flag->prec == 0)
	{
		remain = 2;
		if (flag->minus != '-')
			i -= remain;
		ft_strncpy(&(*temp)[i], str, remain);
	}
	else
	{
		remain = ft_str_i_calc(flag->len, flag);
		if (flag->minus != '-')
			i -= remain;
		ft_strncpy(&(*temp)[i], str, remain);
	}
}

/*	calculations of printing the string	*/

static void	ft_str_print(char *str, t_flag *flag, int total)
{
	if (flag->spec == 'p' && ft_strcmp(str, "0x0") == 0 && flag->prec == 0)
		total = 2;
	else if (str[0] == '\0' && flag->spec == 'c')
	{
		if (!(flag->width < 0))
			total--;
		else
			return ;
	}
	if (flag->width == 0)
		return ;
	flag->str = ft_strnew(total);
	if (!flag->str)
	{
		ft_str_error(str, flag);
		return ;
	}
	ft_memset(flag->str, ' ', total);
	if (flag->minus == '1')
		ft_cpy_to_temp_str(&flag->str, str, flag, total);
	else
		ft_cpy_to_temp_str(&flag->str, str, flag, 0);
	flag->ret += write(1, flag->str, total);
	ft_strdel(&str);
	ft_strdel(&flag->str);
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
		ft_strncpy(str, str_arg, 1);
	else if (!str_arg)
		ft_strcpy(str, "(null)");
	else
		ft_strcpy(str, str_arg);
	return (str);
}

/*	calls function that will calculate string	*/

static void	ft_print_str(char *str, t_flag *flag)
{
	if (str[0] == '\0' && flag->spec == 'c')
		flag->ret += 1;
	if (!str)
		ft_str_error(str, flag);
	ft_print_calc(str, flag, &ft_str_print);
}

/*	narrows down specifier and get arg	*/

void	ft_csp_print(const char *format, t_flag *flag, va_list *arg)
{
	char	c;
	char	*str;

	str = NULL;
	flag->zero = '1';
	if (*format == 'c')
	{
		c = (char)va_arg(*arg, int);
		flag->spec = 'c';
		str = ft_str_creater(&c, flag->spec);
	}
	else if (*format == 's')
	{
		flag->spec = 's';
		str = ft_str_creater((char *)va_arg(*arg, char *), flag->spec);
	}
	else if (*format == 'p')
	{
		flag->spec = 'p';
		str = addr_to_str((unsigned long long)va_arg(*arg, unsigned long long));
	}
	ft_print_str(str, flag);
}
