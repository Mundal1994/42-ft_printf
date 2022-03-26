/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:21:22 by molesen           #+#    #+#             */
/*   Updated: 2022/03/26 16:21:24 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	calculates if we use bankers rounding or not	*/

static int	ft_bankers_rounding(char *str, int *i)
{
	int	count;
	int	nbr;
	int	index;

	count = 0;
	index = *i + 2;
	while (str[index] != '\0')
	{
		if (str[index] != '0')
			count++;
		index++;
	}
	if (count == 0)
	{
		nbr = (int)str[*i] - '0';
		if (nbr % 2 != 0)
			str[*i] = str[*i] + 1;
	}
	else
		str[*i] = str[*i] + 1;
	return (0);
}

/*	puts correct rounded number in str	*/

static int	ft_change_number(char *str, int five, int add, int *i)
{
	if (str[*i] == '9')
	{
		str[*i] = '0';
		add = 1;
	}
	else if (five == TRUE)
	{
		add = ft_bankers_rounding(str, i);
		five = FALSE;
	}
	else
	{
		str[*i] = str[*i] + 1;
		add = 0;
	}
	return (add);
}

/*	correct ending to float calculator based on precision	*/

static int	ft_correct_end_loop(char *str, int total, int add, int *i)
{
	int	five;

	five = FALSE;
	while (str[*i] && (*i >= total || add == 1))
	{
		if (str[*i] == '.')
			*i -= 1;
		if (add == 1)
			add = ft_change_number(str, five, add, i);
		if (str[*i] >= '5' && *i >= total)
		{
			if (str[*i] == '5')
				five = TRUE;
			str[*i] = str[*i] - 1;
			add = 1;
		}
		*i -= 1;
	}
	return (add);
}

/*	correct ending to float calculator based on precision	*/

void	ft_check_correct_end(char *str, int len, int dot)
{
	int		i;
	int		total;
	int		add;
	char	*temp;

	i = dot + len;
	total = dot + len;
	add = 0;
	add = ft_correct_end_loop(str, total, 0, &i);
	if (add == 1)
	{
		temp = ft_strnew(ft_strlen(str));
		ft_strcpy(temp, str);
		ft_strdel(&str);
		str = ft_strnew(ft_strlen(temp) + 1);
		str[0] = '1';
		ft_strcpy(&str[1], temp);
		ft_strdel(&temp);
	}
}
