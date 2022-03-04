/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:00:37 by molesen           #+#    #+#             */
/*   Updated: 2022/02/22 13:00:39 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_i_reset(const char *format, t_flag *flag)
{
	int		i;

	i = 0;
	while (format[i - 1] != '%')
		i--;
	i *= -1;
	flag->i += i;
}

int	ft_convert_symbol(const char *format, t_flag *flag, va_list *arg)
{
	if (*format == 'c' || *format == 's' || *format == 'p')
	{
		ft_csp_print(format, flag, arg);
		return (TRUE);
	}
	else if (*format == 'd' || *format == 'i' || *format == 'u' || *format == 'f')
	{
		ft_diuf_print(format, flag, arg);
		return (TRUE);
	}
	else if (*format == 'o' || *format == 'x' || *format == 'X')
	{
		ft_oxX_print(format, flag, arg);
		return (TRUE);
	}
	return (FALSE);
}

//di difference - has to figure out if there is one
//oxX - still errors when it comes to minus values and x doesn't always print lower characters
