/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:04 by jboon             #+#    #+#             */
/*   Updated: 2024/12/03 15:32:15 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdbool.h>
# include <stdint.h>

# define HEX_LOWER	"0123456789abcdef"
# define HEX_UPPER	"0123456789ABCDEF"
# define DECIMAL	"0123456789"

typedef struct s_nbr		t_nbr;
typedef unsigned long int	t_ulint;
typedef void (convert) (char *dst, t_nbr *data);

typedef struct s_format
{
	int			flags;
	int			width;
	int			precis;
}	t_format;

typedef struct s_nbr
{
	t_ulint	nbr;
	int		nbr_cnt;
	int		str_len;
	bool	is_minus;
	char	*base;
	char	*pre;
}	t_nbr;

enum	e_print_flag
{
	PREFIX = 0x01,
	ZERO_PAD = 0x02,
	LEFT_ALIGN = 0x04,
	BLANK_SIGN = 0x08,
	SHOW_SIGN = 0x10,
};

int			ft_printf(const char *s, ...);
char		*ft_printf_char(char c, t_format *f, int *str_len);
char		*ft_printf_str(char *src, t_format *f, int *str_len);
char		*ft_printf_ptr(void *ptr, t_format *f, int *str_len);
char		*ft_printf_hex(t_ulint nbr, t_format *f, bool large, int *str_len);
char		*ft_printf_int(int nbr, t_format *f, int *str_len);
char		*ft_printf_uint(t_ulint nbr, t_format *f, bool is_minus, int *len);
void		ft_printf_size(t_nbr *d, t_format *f, bool is_minus);

const char	*ft_parse_format(const char *s, t_format *f);
bool		ft_empty_str(char **dst, int str_len);
char		*handle_uint(t_ulint nbr, t_format *f, int *str_len);
char		*handle_hex(const char c, t_ulint nbr, t_format *f, int *str_len);
void		left_align_nbr(char *dst, t_format *f, t_nbr *d, convert conv);
void		right_align_nbr(char *dst, t_format *f, t_nbr *d, convert conv);

int			ft_count_digits(t_ulint nbr);
int			ft_count_pow2(t_ulint nbr, int pow);
#endif
