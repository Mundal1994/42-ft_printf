#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct	s_flag
{
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

int	ft_printf(const char *format, ...);
int	ft_flag_check(const char *format, t_flag *flag, int on);
int	ft_convert_symbol(const char *format, t_flag *flag, va_list *arg);

#endif
