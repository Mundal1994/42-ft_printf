/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:56:27 by molesen           #+#    #+#             */
/*   Updated: 2022/03/23 10:56:29 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_space_zero_calc_digit(t_flag *flag, int len)
{
	char	zero;
	char	space;

	zero = '0';
	space = ' ';
	if (flag->prec < flag->width && flag->prec != -1 && (spec_check(flag, 'd', 'o', 'n') == TRUE))
	{
		while (len++ < flag->width)
			flag->ret += write(1, &space, 1);
	}
	else if (flag->prec >= 0 && flag->prec > len && flag->spec != 'f')
	{
		while (len++ < flag->prec)
			flag->ret += write(1, &zero, 1);
	}
	else if (flag->zero == '0' && flag->prec == -1 && flag->minus == '1')
	{
		while (len++ < flag->width)
			flag->ret += write(1, &zero, 1);
	}
	else
	{
		while (len++ < flag->width)
			flag->ret += write(1, &space, 1);
	}
}

void	ft_plus_print(char *str, t_flag *flag)
{
	char	space;
	char	minus;

	space = ' ';
	minus = '-';
	if (flag->spec != 'u' && str[0] != '-')
	{
		if (flag->plus == '+')
			flag->ret += write(1, &flag->plus, 1);
		else if ((flag->width != -1 && flag->zero != '0') || flag->space == ' ')
			flag->ret += write(1, &space, 1);
	}
	else if (str[0] == '-' && flag->spec != 'u')
	{
		flag->ret += write(1, &minus, 1);
		flag->plus = '1';
	}
}
/*
static int	ft_len_calc(char *str, t_flag *flag)
{
	int	len;

	if (flag->spec == 's')
	{
		len = flag->prec;
		if (flag->prec == -1 || flag->prec == flag->width)
			len = ft_strlen(str);
	}
	else
	{
		len = ft_strlen(str);
	}
	return (len);
}

static void	ft_print_calc_helper(char *str, t_flag *flag, int len, void (*f)(t_flag *, int, char *))
{
	if (flag->minus == '-' && flag->prec < flag->width)
	{
		ft_prec_calc(str, flag);
		f(flag, len, str);
	}
	else
	{
		f(flag, len, str);
		ft_prec_calc(str, flag);
	}
}*/
/*
static void	ft_prec_calculator(char **temp, char *str, t_flag *flag, int c)
{
	int		count;
	int		len;

	if (flag->prec == 0)
	{
		*temp = "\0";
		return ;
	}
	count = 0;
	len = ft_strlen(str);
	if (str[0] == '-' && c == '0')
	{
		(*temp)[0] = '-';
		count = 1;
		len--;
		if (flag->prec == len)
			flag->prec++;
	}
	while (count < flag->prec - len)
	{
		(*temp)[count++] = c;
	}
	if (c == ' ')
		ft_strncpy(&(*temp)[count], str, flag->prec);
	else if (str[0] == '-')
		ft_strcpy(&(*temp)[count], &str[1]);
	else
		ft_strcpy(&(*temp)[count], str);
}*/


static int	ft_check_flags(char *str, t_flag *flag, int total, int len)
{
	//if (str[0] == '-' && spec_check(flag, 'd', 'u', 'f') == TRUE)
	//	len++;
	if (spec_check(flag, 'o', 'x', 'X') == TRUE)
	{
		if (ft_strcmp(str, "0") == 0 && flag->width < flag->prec && flag->prec == 0)
		{
			if (flag->spec == 'o' && flag->hash == TRUE)
				return (1);
			return (0);
		}
		if (flag->hash == TRUE)
		{
			if (flag->width == -1 && flag->prec == -1 && ft_strcmp(str, "0") == 0)
				return (total);
			if (flag->width < len || flag->prec > len)
			{
				if (flag->spec == 'o')
				{
					if (flag->prec <= len)
						return (++total);
					if (flag->width < flag->prec)
						return (total);
				}
				total++;
				if (spec_check(flag, 'n', 'x', 'X') == TRUE)
					total++;
			}
		}
	}
	if (flag->spec == 'c' && str[0] == '\0' && flag->width > 0)
		total--;
	if (flag->spec == 'p' && ft_strcmp(str, "0x0") == 0 && flag->prec == 0)
		total = 2;
	if (spec_check(flag, 'd', 'u', 'f') == TRUE)
	{
		if (flag->spec == 'f' && flag->prec < len && flag->width == -1)
		{
			if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
				total++;
			return (total);
		}
		if ((flag->width <= len && (flag->width <= flag->prec || flag->spec == 'f')) || (flag->prec >= len && flag->prec > flag->width && flag->spec != 'f'))
		{
			if (str[0] == '-' && (flag->width > -1 || flag->prec > -1))
				total++;
			else if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
				total++;
		}
	}
	if (spec_check(flag, 'd', 'u', 'f') == TRUE)
		if (ft_strcmp(str, "0") == 0 && flag->prec == 0 && flag->width == -1)
			total--;
	return (total);
}

static int	ft_len_calculator(t_flag *flag, int len)
{
	if (flag->width == -1 && flag->prec == -1)
		return (len);
	else if (flag->prec > flag->width && flag->spec == 'f')
		return (len);
	else if (flag->width < len && flag->prec == -1 && spec_check(flag, 'c', 's', 'n') == TRUE)
		return (len);
	else if (flag->width > flag->prec && (flag->width > len || spec_check(flag, 'c', 's', 'n') == TRUE))
		return (flag->width);
	else if (flag->prec > len && flag->width == -1)
	{
		if (spec_check(flag, 'c', 's', 'n') == TRUE)
			return (len);
		else
			return (flag->prec);
	}
	else if (flag->prec >= flag->width && (flag->prec >= len || spec_check(flag, 'c', 's', 'p') == TRUE))
		return (flag->prec);
	return (len);
}
/*
static void	ft_width_calc(char *str, flag)
{

}*/

void	ft_print_calc(char *str, t_flag *flag, void (*f)(t_flag *, int, char *))
{
	int		len;
	char	*temp;
	int		total;
	//int		pnt;

	len = ft_strlen(str);
	total = ft_len_calculator(flag, len);
	total = ft_check_flags(str, flag, total, len);
	//if (flag->spec == 'p' && flag->width < len && flag->prec < len)
	//	total += 2;
	//ft_putstr(str);
	temp = ft_strnew(total);
	if (!temp)
		return (ft_putstr_fd("error\n", 2));
	ft_memset(temp, ' ', total);
	ft_putstr(temp);
	//if (str[0] == '-' && flag->width < flag->prec)// put this inside prec calc function
	//	len--;
	//if (flag->minus == '-')
	//{
		/*
		if minus go to right end and call all the functions in reverse order and calculate where to be in temp from there
		ex
		if minus
			pnt = total;
			if (flag->prec > -1)
				pnt -= len - 1;
				call precision function &temp[pnt]
			if (flag->zero == '0' && ...)
				pnt recalculate
				call zero function
			call plus function
				pnt--;
				plus function (&temp[pnt]);
			if hash
				pnt recalculate
				call hash function
		else
		{
			if (plus)
				call plus function
				pnt++
			if (special char like hash)
				call hash function
			if (flag->zero)
			if prec
		}
		*/
	//}
	/*if (flag->prec > -1)
	{
		if (spec_check(flag, 'c', 's', 'p') == TRUE)
			ft_prec_calculator(&temp, str, flag, ' ');
		else if (flag->prec >= len && spec_check(flag, 'c', 's', 'p') == FALSE)
			ft_prec_calculator(&temp, str, flag, '0');
		ft_putstr(temp);
	}*/
/*	if (flag->zero == '0' && flag->width > len && flag->prec == -1)
	{
		if (flag->prec >= len)
			ft_prec_calculator(&str, flag, len, '0');
			// precision is not going to quite work here due to it not taking first thing into consideration as flag->width does
	}*/
	//if (flag->width > len)
	//	ft_width_calc(str, flag)
	if (f)
		ft_putstr("");
	/*
	int len

	len = ft_strlen(str);
	keep track of if neg here
	if (str[0] == '-' && flag->width < flag->prec) // put this inside prec calc function
		len--;
	if (flag->prec > -1 && flag->prec >= len)
		ft_prec_calc(str, flag);

	if (flag->zero == '0' && flag->width > len && prec == -1)
		ft_prec_calc(str, flag);(reuse logic - check inside if -)
	if (flag->space == ' ' || flag->plus == '+')
		ft_plus_space_add(str, flag);
	if (something specific for a group print it here ex 0x, 0 or something)
	if (flag->minus == '-')
		ft_change_order_of_applying width (maybe do that check inside this function)
	if (flag->width > len)
		ft_width_calc(str, flag);
	at this point we should have manipulated string and copy it inside string inside struct or maybe just print it here
	*/
	/*
	int	len;

	len = ft_len_calc(str, flag);
*/
	/*
	if (str[0] == '-')
	{
		flag->plus = '+';
		if (flag->prec != -1 && (flag->prec < flag->width || flag->prec >= len))
			len--;
	}
	if (((flag->space == ' ' && flag->minus == '1') || flag->prec > flag->width || flag->zero == '0') && \
		(spec_check(flag, 'd', 'f', 'u') == TRUE))
		ft_plus_print(str, flag);
	else if ((spec_check(flag, 'o', 'x', 'X') == TRUE) && flag->width <= flag->prec)
		ft_prec_calc_ox(str, flag, TRUE);
	if (flag->width >= 0 || flag->prec >= 0)
		ft_print_calc_helper(str, flag, len, f);
	else
		ft_prec_calc(str, flag);*/
	//ft_strdel(&str);
}
