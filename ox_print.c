/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ox_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:05:12 by molesen           #+#    #+#             */
/*   Updated: 2022/03/04 10:05:14 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	*ft_hash2_print(char *temp, t_flag *flag, int *index)
{
	ft_memset(temp, '0', 1);
	(*index)++;
	if (flag->spec == 'x')
	{
		(*index)++;
		ft_memset(&temp[1], 'x', 1);
	}
	if (flag->spec == 'X')
	{
		(*index)++;
		ft_memset(&temp[1], 'X', 1);
	}
	return (temp);
}


static void	*ft_check_hash(char *temp, char *str, t_flag *flag, int *index)
{
	int	len;

	len = ft_strlen(str);
	if (flag->hash == TRUE && flag->minus == '1')
	{
		if (flag->spec == 'o' || (len > flag->width - 2 && len > flag->prec))
			ft_hash2_print(temp, flag, index);
		
	}
	//else if (len > flag->width && len > flag->prec)
	//	ft_hash2_print(temp, flag, index);
	//else if (flag->prec > flag->width)
	//	ft_hash2_print(temp, flag, index);
	//else if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
	//	ft_hash2_print(temp, flag, index);
	
	return (temp);
}
/*
static void	*ft_check_hash_rigth(char *temp, char *str, t_flag *flag, int *index)
{
	int	len;

	len = ft_strlen(str);
	
	if ((flag->minus == '-' || (len > flag->width - 2 && len > flag->prec)) && flag->hash == TRUE)
		ft_hash2_print(temp, flag, index);
	else
			ft_hash2_print(&temp[-1], flag, index);
	
	return (temp);
}
*/
static void	ft_if_prec_calc(char *str, t_flag *flag, int *index, int total)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == '-')
		len--;
	if (flag->prec < flag->width && flag->prec > len && flag->minus == '1')
	{
		ft_memset(&flag->str[*index], ' ', flag->width - flag->prec);
		//ft_check_hash_rigth(&flag->str[flag->width - flag->prec - 1], str, flag, index);
		ft_memset(&flag->str[flag->width - flag->prec], '0', flag->prec);
	}
	else if (flag->prec < flag->width && flag->prec > len && flag->minus == '-')
	{
		ft_memset(&flag->str[*index], '0', flag->prec);
		ft_memset(&flag->str[flag->width - flag->prec + *index], ' ', flag->width - flag->prec - *index);
	}
	else if (flag->prec > len && flag->width < flag->prec)
		ft_memset(&flag->str[*index], '0', flag->prec);
	else if (flag->width > len)
	{
		ft_memset(&flag->str[*index], ' ', total - *index);
		//ft_check_hash_rigth(&flag->str[flag->width - len - 1], str, flag, index);
	}
	else
		ft_memset(&flag->str[*index], ' ', total - *index);
}

void	ft_set_base_str_ox(char *str, t_flag *flag, int total, int len)
{
	int	index;

	index = 0;
	ft_check_hash(&flag->str[index], str, flag, &index);
	if (index == -1)
		index = 0;
	if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
		ft_memset(&flag->str[index], '0', total);
	else if (flag->prec > -1)
		ft_if_prec_calc(str, flag, &index, total);
	else if (flag->width > 0 && flag->width > len)
	{
		ft_memset(&flag->str[index], ' ', total - index);
		ft_check_hash(&flag->str[flag->width - len - 1], str, flag, &index);
	}
	else
		ft_memset(&flag->str[index], ' ', total);
}

static void	ft_striter_uplow(char *str, int (*f)(int))
{
	int	i;

	i = 0;
	if (str && f)
	{
		while (str[i] != '\0')
		{
			str[i] = f(str[i]);
			i++;
		}
	}
}

static char	*ft_convert_length_ox(char *str, t_flag *flag,
			unsigned long long nbr)
{
	int	specifier;

	if (flag->spec == 'o')
		specifier = 8;
	else
		specifier = 16;
	if (flag->hh == TRUE)
		str = ft_ulltoa_base((unsigned char)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->h == TRUE)
		str = ft_ulltoa_base((unsigned short)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->l == TRUE)
		str = ft_ulltoa_base((unsigned long)nbr, ft_ulong_len(nbr), specifier);
	else if (flag->ll == TRUE)
		str = ft_ulltoa_base(nbr, ft_ulong_len(nbr), specifier);
	else
		str = ft_ulltoa_base((unsigned int)nbr, ft_ulong_len(nbr), specifier);
	return (str);
}

void	ft_ox_print(const char *format, t_flag *flag, va_list *arg)
{
	unsigned long long	nbr;
	char				*str;

	nbr = va_arg(*arg, unsigned long long);
	str = NULL;
	if (*format == 'o')
	{
		flag->spec = 'o';
		str = ft_convert_length_ox(str, flag, nbr);
		ft_print_calc(str, flag, &ft_digit_print);
	}
	else if (*format == 'x')
	{
		flag->spec = 'x';
		str = ft_convert_length_ox(str, flag, nbr);
		ft_striter_uplow(str, &ft_tolower);
		ft_print_calc(str, flag, &ft_digit_print);
	}
	else if (*format == 'X')
	{
		flag->spec = 'X';
		str = ft_convert_length_ox(str, flag, nbr);
		ft_striter_uplow(str, &ft_toupper);
		ft_print_calc(str, flag, &ft_digit_print);
	}
}
