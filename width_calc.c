/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:20:07 by molesen           #+#    #+#             */
/*   Updated: 2022/03/24 20:20:09 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	if ox specifier we do these flag checks and adds to the total length	*/

static int	ft_check_flags_ox(char *str, t_flag *flag, int total)
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
		if (flag->width < flag->len || flag->prec > flag->len)
		{
			if (flag->spec == 'o')
			{
				if (flag->prec <= flag->len)
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

/*	adds to length if any flags are present	*/

static int	ft_check_flags(char *str, t_flag *flag, int total)
{
	if (spec_check(flag, 'o', 'x', 'X') == TRUE)
		return (ft_check_flags_ox(str, flag, total));
	if (spec_check(flag, 'd', 'n', 'f') == TRUE)
	{
		if (!(flag->len > flag->width && flag->len > flag->prec && \
			(str[0] == '-' || str[0] == '+')))
			if (flag->width < flag->len)
				return (ft_check_flags_digit(str, flag, total, flag->len));
	}
	return (total);
}

static int	ft_len_calc_helper(t_flag *flag, int i)
{
	if (i == 0)
	{
		if (spec_check(flag, 'c', 's', 'n') == TRUE)
			return (flag->len);
		else
			return (flag->prec);
	}
	else
	{
		if (spec_check(flag, 'c', 's', 'p') == TRUE && flag->prec > flag->len)
		{
			if (flag->width > flag->len)
				return (flag->width);
			return (flag->len);
		}
		return (flag->prec);
	}
}

/*	calculates length based on precision and width	*/

static int	ft_len_calculator(t_flag *flag)
{
	if (flag->width == -1 && flag->prec == -1)
		return (flag->len);
	else if (flag->prec > flag->width && flag->spec == 'f')
		return (flag->len);
	else if (flag->width < flag->len && flag->prec == -1 && \
		spec_check(flag, 'c', 's', 'n') == TRUE)
		return (flag->len);
	else if (flag->width > flag->prec && (flag->width > flag->len || \
		spec_check(flag, 'c', 's', 'n') == TRUE))
		return (flag->width);
	else if (flag->prec > flag->len && flag->width == -1)
		return (ft_len_calc_helper(flag, 0));
	else if (flag->prec >= flag->width && (flag->prec >= flag->len || \
		spec_check(flag, 'c', 's', 'p') == TRUE))
		return (ft_len_calc_helper(flag, 1));
	return (flag->len);
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

/*	calculates length of str that needs to be malloced	*/

void	ft_print_calc(char *str, t_flag *flag, void (*f)(char *, t_flag *, int))
{
	int		total;
	int		len_until_dec;
	int		decimal_len;
	char	*temp;

	flag->len = ft_strlen(str);
	if (flag->spec == 'f' && flag->prec == -1)
	{
		len_until_dec = ft_strlen_stop(str, '.') + 1;
		decimal_len = ft_strlen(&str[len_until_dec]);
		if (decimal_len != 6)
		{
			temp = str;
			str = ft_strjoin(temp, "0");
			ft_strdel(&temp);
			flag->len++;
		}
	}
	total = ft_len_calculator(flag);
	total = ft_check_flags(str, flag, total);
	f(str, flag, total);
}
