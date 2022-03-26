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

static int	ft_check_flags_ox(char *str, t_flag *flag, int total, int len)
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
	return (total);
}

static int	ft_check_flags(char *str, t_flag *flag, int total, int len)
{
	if (spec_check(flag, 'o', 'x', 'X') == TRUE)
		return (ft_check_flags_ox(str, flag, total, len));
	if (spec_check(flag, 'd', 'n', 'f') == TRUE)
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
		if (ft_strcmp(str, "0") == 0 && ft_strlen(str) == 0 && flag->prec == 0 && flag->width == -1)
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

int	ft_str_i_calc(int len, t_flag *flag)
{
	int	dif;

	dif = flag->prec - len;
	if (dif < 0)
	{
		if (flag->prec == -1)
			return (len);
		return (flag->prec);
	}
	return (len);
}
/*
static void	ft_cpy_to_temp(char **temp, char *str, t_flag *flag, int *i)
{
	int	remain;
	int	len;

	len = ft_strlen(str);
	if (flag->minus != '-')
	{
		if (spec_check(flag, 'c', 's', 'p') == TRUE)
		{
			remain = ft_str_i_calc(len, flag);
			*i -= remain;
			ft_strncpy(&(*temp)[*i], str, remain);
			return ;
			//can i just return here if it is c s or p??
		}
		*i -= len;
		if (str[0] == '-')
			ft_strcpy(&(*temp)[*i], &str[1]);
		else
			ft_strcpy(&(*temp)[*i], str);
	}
	else
	{
		if (spec_check(flag, 'c', 's', 'p') == TRUE)
		{
			remain = ft_str_i_calc(len, flag);
			ft_strncpy(*temp, str, remain);
			return ;
		}
		if (str[0] == '-')
			ft_strcpy(*temp, &str[1]);
		else
			ft_strcpy(*temp, str);
	}

}*/
/*
static void	ft_prec_calculator(char **temp, t_flag *flag, int len, int *i)
{
	int		dif;

	dif = flag->prec - len;
	if (flag->minus == '1' && dif > 0)
	{
		while (*i > dif)
		{
			if ((*temp)[*i] == ' ')
				(*temp)[(*i)--] = '0';
		}
	}
	else if (dif > 0)
	{
		while (*i < dif)
		{
			if ((*temp)[*i] == ' ')
				(*temp)[(*i)++] = '0';
		}
	}
}*/
/*
static int	ft_add_sign(char **temp, char *str, t_flag *flag)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		(*temp)[i++] = '-';
	}
	else if (flag->plus == '+')
	{
		(*temp)[i++] = '+';
	}
	else if (flag->space == ' ')
	{
		(*temp)[i++] = ' ';
	}
	else if (flag->hash == TRUE && spec_check(flag, 'o', 'x', 'X') == TRUE)
	{
		if (flag->spec == 'x')
		{
			(*temp)[i++] = '0';
			(*temp)[i++] = 'x';
		}
		else if (flag->spec == 'X')
		{
			(*temp)[i++] = '0';
			(*temp)[i++] = 'X';
		}
		else
		{
			(*temp)[i++] = '0';
		}
	}
	return (i);
}*/

void	ft_print_calc(char *str, t_flag *flag, void (*f)(char *, t_flag *, int, int))
{
	int		len;
	//char	*temp;
	int		total;
//	int		i;

	len = ft_strlen(str);
	total = ft_len_calculator(flag, len);
	total = ft_check_flags(str, flag, total, len);
	f(str, flag, len, total);
	/*temp = ft_strnew(total);
	if (!temp)
		return (ft_putstr_fd("error\n", 2));
	if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
		ft_memset(temp, '0', total);
	else if (flag->prec > -1 && spec_check(flag, 'c', 's', 'p') == FALSE)
	{
		if (flag->prec < flag->width && flag->prec > len && flag->minus == '1')
		{
			ft_memset(temp, ' ', flag->width - flag->prec);
			ft_memset(&temp[flag->prec], '0', flag->prec);
		}
		else if (flag->prec < flag->width && flag->prec > len && flag->minus == '-')
		{
			ft_memset(temp, '0', flag->prec);
			ft_memset(&temp[flag->prec], ' ', flag->width - flag->prec);
		}
		else if (flag->prec > len)
			ft_memset(temp, '0', flag->prec);
		else
			ft_memset(temp, ' ', total);
	}
	else
		ft_memset(temp, ' ', total);
	if (str[0] == '-' && spec_check(flag, 'd', 'u', 'f') == TRUE)// put this inside prec calc function
		len--;
	if (flag->minus == '1')
	{
		i = total;
		ft_cpy_to_temp(&temp, str, flag, &i);*/
		//if (flag->prec > -1 && spec_check(flag, 'c', 's', 'p') == FALSE)
		//{
		//	ft_prec_calculator(&(&temp)[i], flag, len, &i);
			//if (flag->prec - len > 0)
			//	i -= flag->prec - len;
			/*i -= ft_prec_calculator(&(&temp)[i], flag, len);*/
		//}
		/*else if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
		{
			ft_putnbr(1);
			// new calculation for adding zeros
		}*/
		/*if (spec_check(flag, 'c', 's', 'p') == FALSE)
		{
			if (flag->plus == '+' || flag->space == ' ' || str[0] == '-' || flag->hash == TRUE)
			{
				i -= ft_add_sign(&(&temp)[i], str, flag);
			}
		}*/
		//flag->ret += write(1, temp, total);
	//}
	//else
	//{
		/*this need to happen last*/
	//	i = 0;
		//i =	flag->prec - len;
		/*if (spec_check(flag, 'c', 's', 'p') == FALSE)
		{
			if (flag->plus == '+' || flag->space == ' ' || str[0] == '-' || flag->hash == TRUE)
			{
				i += ft_add_sign(&(&temp)[i], str, flag);
			}
		}*/
		// it segmentfault at this end...
		//if (flag->prec > -1 && spec_check(flag, 'c', 's', 'p') == FALSE)
		//{
		//	ft_prec_calculator(&(&temp)[i], flag, len, &i);
			//i += ft_prec_calculator(&(&temp)[i], flag, len);
		//}
		/*else if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
		{
			ft_putnbr(1);
			// new calculation for adding zeros
		}*/
	/*	ft_cpy_to_temp(&temp, str, flag, &i);
		flag->ret += write(1, temp, total);
		//ft_putstr(temp);
		if (spec_check(flag, 'c', 's', 'p') == TRUE)
			return ;*/
		//ft_putstr(temp);
//	}
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
	//if (f)
	//	ft_putstr("");
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
	//ft_strdel(&str);
	//ft_strdel(&temp);
}
