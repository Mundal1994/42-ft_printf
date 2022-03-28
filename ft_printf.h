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
	char		*str;
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
	int			len;
	int			star_w;
	int			star_p;
}				t_flag;

int		ft_printf(const char *format, ...);
void	ft_flag_checker(const char *format, t_flag *flag, va_list *arg);
int		ft_specifier_check(const char *format, t_flag *flag, va_list *arg);
void	ft_print_calc(char *str, t_flag *flag, void (*f)(char *, t_flag *, \
		int));
void	ft_digit_print(char *str, t_flag *flag, int total);
void	ft_csp_print(const char *format, t_flag *flag, va_list *arg);
void	ft_diu_print(const char *format, t_flag *flag, va_list *arg);
void	ft_ox_print(const char *format, t_flag *flag, va_list *arg);
void	ft_fp_print(const char *format, t_flag *flag, va_list *arg);
int		spec_check(t_flag *flag, int a, int b, int c);
char	*ft_ftoa(long double number, int len);
void	ft_check_correct_end(char *str, int len, int dot);
long	ft_flong_len(double nbr);
void	ft_i_reset(const char *format, t_flag *flag);
int		ft_color_print(const char *str, t_flag *flag);
int		ft_str_i_calc(int len, t_flag *flag);
void	ft_set_base_str(char *str, t_flag *flag, int total);
int		ft_check_flags_digit(char *str, t_flag *flag, int total);
void	*ft_hash_sign_check(char *temp, char *str, t_flag *flag, int *i);
void	*ft_hash_print(char *temp, t_flag *flag, int *index);
void	ft_flag_adjuster(t_flag *flag);
void	ft_str_error(char *str, t_flag *flag);
void	ft_error(char *str, t_flag *flag);

#endif
