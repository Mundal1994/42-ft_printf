/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:47:19 by molesen           #+#    #+#             */
/*   Updated: 2022/03/01 12:47:21 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_float_flags(char *str, t_flag *flag, int total, int len)
{
	if (flag->prec < len && flag->width == -1)
	{
		if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
			total++;
	}
	else if (flag->width <= len)
	{
		if (str[0] == '-' && (flag->width > -1 || flag->prec > -1))
			total++;
		else if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
			total++;
	}
	return (total);
}
static int	ft_check_flags_digit(char *str, t_flag *flag, int total, int len)
{
	if (flag->spec == 'f')
		return (ft_check_float_flags(str, flag, total, len));
	else
	{
		if ((flag->width <= len && flag->width <= flag->prec) || (flag->prec >= len && flag->prec > flag->width))
		{
			if (str[0] == '-' && (flag->width > -1 || flag->prec > -1))
				total++;
			else if ((flag->plus == '+' || flag->space == ' ') && str[0] != '-')
				total++;
		}
		if (ft_strcmp(str, "0") == 0 && flag->prec == 0 && flag->width == -1)
			total--;
		if (flag->plus == '+' && flag->minus == '-')
			total++;
		else if (flag->plus == '+' && flag->width > flag->prec && flag->width > len)
			total++;
	}
	return (total);
}

static void	ft_cpy_to_temp_digit(char **temp, char *str, t_flag *flag, int i)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == '-')
		len--;
	if (flag->minus != '-')
		i -= len;
	if (flag->prec == 0 && ft_strcmp(str, "0") == 0)
		(*temp)[i] = ' ';
	else if (str[0] == '-')
		ft_strcpy(&(*temp)[i], &str[1]);
	else
		ft_strcpy(&(*temp)[i], str);
}

/*
**	calculate the amount of space we need to consider when printing digits
**	narrows down what extra needs to be printed to have correct width
*/

static void	ft_put_plus_space_minus(char **temp, char *str, t_flag *flag, int *index)
{
	if (str[0] == '-')
	{
		ft_memset(*temp, '-', 1);
		(*index)++;
	}
	else if (flag->plus == '+')
	{
		ft_memset(*temp, '+', 1);
		(*index)++;
	}
	else if (flag->space == ' ')
	{
		ft_memset(*temp, ' ', 1);
		(*index)++;
	}
}

static void	ft_check_plus_space_minus_left(char **temp, char *str, t_flag *flag, int *index)
{
	int	len;

	len = ft_strlen(str);
	if (flag->minus == '-')
		ft_put_plus_space_minus(temp, str, flag, index);
	else if (len > flag->width && len > flag->prec)
		ft_put_plus_space_minus(temp, str, flag, index);
	else if (flag->prec > flag->width)
		ft_put_plus_space_minus(temp, str, flag, index);
	else if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
		ft_put_plus_space_minus(temp, str, flag, index);

}

static void	ft_check_plus_space_minus_left_rigth(char **temp, char *str, t_flag *flag, int *index)
{
	if (flag->minus == '1')
	{
		ft_put_plus_space_minus(temp, str, flag, index);
	}
}

void	ft_digit_print(char *str, t_flag *flag, int len, int total)
{
	char	*temp;
	int		i;
	int		new_total;
	int		index;

	if (flag->prec == 0 && ft_strcmp(str, "0") == 0 && flag->width == -1)
		return ;
	temp = ft_strnew(total);
	if (!temp)
		return (ft_putstr_fd("error\n", 2));
	index = 0;
	ft_check_plus_space_minus_left(&(&temp)[index], str, flag, &index);
	if (str[0] == '-' && spec_check(flag, 'd', 'n', 'f') == TRUE)
		len--;
	if (flag->zero == '0' && flag->width > 0 && flag->prec == -1)
		ft_memset(&temp[index], '0', total);
	else if (flag->prec > -1)
	{
		if (flag->prec < flag->width && flag->prec > len && flag->minus == '1')
		{
			ft_memset(&temp[index], ' ', flag->width - flag->prec);
			ft_check_plus_space_minus_left_rigth(&(&temp)[flag->width - flag->prec - 1], str, flag, &index);
			ft_memset(&temp[flag->width - flag->prec], '0', flag->prec);
		}
		else if (flag->prec < flag->width && flag->prec > len && flag->minus == '-')
		{
			
			ft_memset(&temp[index], '0', flag->prec);
			ft_memset(&temp[flag->width - flag->prec + index], ' ', flag->width - flag->prec - index);
		}
		else if (flag->prec > len && flag->width < flag->prec)
		{
			
			ft_memset(&temp[index], '0', flag->prec);
		}
		else if (flag->width > len)
		{
			//here
			/*ft_putstr("HERE\n");
			ft_putnbr(len);
			ft_putchar('\n');*/
			/*int new_len = flag->width - len - 1;
			if (new_len < 0)
				new_len = 0;*/
			ft_check_plus_space_minus_left_rigth(&(&temp)[flag->width - len - 1], str, flag, &index);
			ft_memset(&temp[index], ' ', total - index);
		}
		else
			ft_memset(&temp[index], ' ', total - index);
	}
	else
		ft_memset(&temp[index], ' ', total);
	if (flag->spec != 'u' && ft_strcmp(str, "0") == 0 && ft_strlen(str) == 0 && flag->prec == 0)
		return ;
	if (flag->minus == '1')
	{
		ft_cpy_to_temp_digit(&temp, str, flag, total);
		i = total - len;
		while (i < total)
		{
			if (temp[i] == '\0')
				temp[i] = ' ';
			i++;
		}
	}
	else
	{
		/*this need to happen last*/
		i = 0;
		new_total = ft_check_flags_digit(str, flag, total, len);
		if (flag->prec > len)
			i =	flag->prec - len;
		if (total < new_total)
			i++;
		ft_cpy_to_temp_digit(&temp, str, flag, i);
		while (i < total)
		{
			if (temp[i] == '\0')
				temp[i] = ' ';
			i++;
		}
	}
	flag->ret += write(1, temp, total);
	ft_strdel(&str);
	ft_strdel(&temp);
}
// unsigned int behaves a bit wierd with the length of printing but it says it prints the correct?
//unsgined int is wierd when minus == '-' && width > prec && prec != -1
/*	convert long long down to wanted length based on flags	*/

static char	*ft_convert_length(char *str, t_flag *flag, long long nbr)
{
	if (flag->hh == TRUE)
		str = ft_itoa_base((signed char)nbr, ft_long_len(nbr), 10);
	else if (flag->h == TRUE)
		str = ft_itoa_base((short)nbr, ft_long_len(nbr), 10);
	else if (flag->l == TRUE)
		str = ft_itoa_base((long)nbr, ft_long_len(nbr), 10);
	else if (flag->ll == TRUE)
		str = ft_itoa_base(nbr, ft_long_len(nbr), 10);
	else
		str = ft_itoa_base((int)nbr, ft_long_len(nbr), 10);
	return (str);
}

/*	convert unsigned long long down to wanted length based on flags	*/

static char	*ft_convert_length_u(char *str, t_flag *flag, unsigned long long \
nbr)
{
	str = ft_strnew(ft_ulong_len(nbr));
	if (flag->hh == TRUE)
		str = ft_ulltoa((unsigned char)nbr, str);
	else if (flag->h == TRUE)
		str = ft_ulltoa((unsigned short)nbr, str);
	else if (flag->l == TRUE)
		str = ft_ulltoa((unsigned long)nbr, str);
	else if (flag->ll == TRUE)
		str = ft_ulltoa(nbr, str);
	else
		str = ft_ulltoa((unsigned int)nbr, str);
	return (str);
}

/*	narrows down the specifier and start calculation for printing	*/

void	ft_diu_print(const char *format, t_flag *flag, va_list *arg)
{
	long long			nbr;
	unsigned long long	var;
	char				*str;

	str = NULL;
	nbr = 0;
	if (flag->minus == '-')
		flag->zero = '1';
	if (*format == 'd' || *format == 'i')
	{
		nbr = va_arg(*arg, long long);
		str = ft_convert_length(str, flag, nbr);
		flag->spec = 'd';
		ft_print_calc(str, flag, &ft_digit_print);
	}
	else if (*format == 'u')
	{
		var = va_arg(*arg, unsigned long long);
		str = ft_convert_length_u(str, flag, var);
		flag->spec = 'u';
		ft_print_calc(str, flag, &ft_digit_print);
	}
}
