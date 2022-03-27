/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sign_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:46:32 by molesen           #+#    #+#             */
/*   Updated: 2022/03/24 19:46:33 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	if the corresponding flag is true we put it into the string	*/

static void	*ft_sign_print(char *temp, char *str, t_flag *flag, int *i)
{
	if (str[0] == '-' && flag->spec != 'u')
	{
		ft_memset(temp, '-', 1);
		(*i)++;
	}
	else if (flag->plus == '+' && flag->spec != 'u')
	{
		ft_memset(temp, '+', 1);
		(*i)++;
	}
	else if (flag->space == ' ')
	{
		ft_memset(temp, ' ', 1);
		(*i)++;
	}
	return (temp);
}

/*	checks sign to put if we try placing digits furthest left	*/

static void	*ft_sign_check_l(char *temp, char *str, t_flag *flag, int *i)
{
	if (spec_check(flag, 'o', 'x', 'X') == TRUE && flag->hash == TRUE)
		ft_hash_sign_check(temp, str, flag, i);
	else if (spec_check(flag, 'd', 'u', 'f') == TRUE)
	{
		if (flag->minus == '-')
			ft_sign_print(temp, str, flag, i);
		else if (flag->len > flag->width && flag->len > flag->prec)
			ft_sign_print(temp, str, flag, i);
		else if (flag->prec > flag->width)
			ft_sign_print(temp, str, flag, i);
		else if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
			ft_sign_print(temp, str, flag, i);
	}
	return (temp);
}

/*	checks sign to put if we try placing digits furthest rigth	*/

static void	*ft_sign_check_r(char *temp, char *str, t_flag *flag, int *index)
{
	if (spec_check(flag, 'o', 'x', 'X') == TRUE && flag->hash == TRUE)
	{
		if (flag->hash == TRUE && flag->minus == '1' && flag->spec != 'o')
			ft_hash_print(&temp[-1], flag, index);
		else if (flag->hash == TRUE && flag->minus == '1' && flag->spec == 'o')
			ft_hash_print(temp, flag, index);
	}
	else if (spec_check(flag, 'd', 'u', 'f') == TRUE && flag->minus == '1')
		ft_sign_print(temp, str, flag, index);
	return (temp);
}

/*	calculations made weather to input space, 0 or other sign into str	*/

static void	ft_if_prec_helper(char *str, t_flag *flag, int *index, int total)
{
	if (flag->prec < flag->width && flag->prec > flag->len && \
		flag->minus == '1')
	{
		ft_memset(&flag->str[*index], ' ', flag->width - flag->prec);
		ft_sign_check_r(&flag->str[flag->width - flag->prec - 1], str, \
		flag, index);
		ft_memset(&flag->str[flag->width - flag->prec], '0', flag->prec);
	}
	else if (flag->prec < flag->width && flag->prec > flag->len && \
		flag->minus == '-')
	{
		ft_memset(&flag->str[*index], '0', flag->prec);
		ft_memset(&flag->str[flag->width - flag->prec + *index], ' ', \
		flag->width - flag->prec - *index);
	}
	else if (flag->prec > flag->len && flag->width < flag->prec)
		ft_memset(&flag->str[*index], '0', flag->prec);
	else if (flag->width > flag->len)
	{
		ft_memset(&flag->str[*index], ' ', total - *index);
		ft_sign_check_r(&flag->str[flag->width - flag->len - 1], str, flag, \
		index);
	}
	else
		ft_memset(&flag->str[*index], ' ', total - *index);
}

/*	puts in space, zero and sign depending on width, prec and flags	*/

void	ft_set_base_str(char *str, t_flag *flag, int total)
{
	int	index;

	index = 0;
	ft_sign_check_l(&flag->str[index], str, flag, &index);
	if (str[0] == '-' && spec_check(flag, 'd', 'n', 'f') == TRUE)
		flag->len--;
	if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
		ft_memset(&flag->str[index], '0', total);
	else if (flag->prec > -1)
		ft_if_prec_helper(str, flag, &index, total);
	else if (flag->width > 0 && flag->width > flag->len)
	{
		ft_memset(&flag->str[index], ' ', total - index);
		ft_sign_check_r(&flag->str[flag->width - flag->len - 1], str, \
		flag, &index);
	}
	else
		ft_memset(&flag->str[index], ' ', total);
}
