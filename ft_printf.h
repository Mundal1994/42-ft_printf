#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

typedef struct	s_flag
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
	int			s_l;
	int			b_l;
	int			flags;
	int			len;
	int			i;
}				t_flag;

int		ft_printf(const char *format, ...);
void	ft_flag_checker(const char *format, t_flag *flag, va_list *arg);
int		ft_specifier_check(const char *format, t_flag *flag, va_list *arg);
void	ft_print_calc(char *str, t_flag *flag, void (*prec)(char *, t_flag *), void (*space)(t_flag *, int));
void	ft_plus_print(t_flag *flag, int len);
void	ft_csp_print(const char *format, t_flag *flag, va_list *arg);
void	ft_diuf_print(const char *format, t_flag *flag, va_list *arg);
void	ft_oxX_print(const char *format, t_flag *flag, va_list *arg);
void	ft_i_reset(const char *format, t_flag *flag);
int		ft_color_print(const char *str, t_flag *flag);

#endif
