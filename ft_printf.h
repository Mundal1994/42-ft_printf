/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:58:06 by molesen           #+#    #+#             */
/*   Updated: 2022/03/15 12:58:09 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

typedef struct s_flag
{
	char		spec;
	int			hash;
	int			space;
	int			minus;
	int			plus;
	int			zero;
	int			width;
	int			prec;
	int			hh;
	int			h;
	int			l;
	int			ll;
	int			b_l;
	int			i;
	int			ret;
}				t_flag;

int		ft_printf(const char *format, ...);
void	ft_flag_checker(const char *format, t_flag *flag, va_list *arg);
int		ft_specifier_check(const char *format, t_flag *flag, va_list *arg);
void	ft_print_calc(char *str, t_flag *flag, void (*f)(t_flag *, int));
void	ft_plus_print(char *str, t_flag *flag);//, int len);
void	ft_space_zero_calc_digit(t_flag *flag, int len);
void	ft_prec_calc(char *str, t_flag *flag);
void	ft_space_calc_csp(t_flag *flag, int len);
void	ft_space_calc_digit(t_flag *flag, int len);
void	ft_space_calc_ox(t_flag *flag, int len);
void	ft_csp_print(const char *format, t_flag *flag, va_list *arg);
void	ft_diu_print(const char *format, t_flag *flag, va_list *arg);
void	ft_ox_print(const char *format, t_flag *flag, va_list *arg);
void	ft_f_print(const char *format, t_flag *flag, va_list *arg);
void	ft_b_print(const char *format, t_flag *flag, va_list *arg);
char	*ft_ftoa(double number, int len);
long	ft_flong_len(double nbr);
void	ft_i_reset(const char *format, t_flag *flag);
int		ft_color_print(const char *str, t_flag *flag);

#endif
