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
}				t_flag;

int	ft_printf(const char *format, ...);

#endif
