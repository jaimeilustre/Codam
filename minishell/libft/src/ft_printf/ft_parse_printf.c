/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_printf.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 13:43:53 by jboon         #+#    #+#                 */
/*   Updated: 2025/01/10 12:00:01 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
	Get the flags (#0- +) out of the format and asign it to flag.
	@return pointer of s after flags.
*/
static const char	*set_flags(const char *s, int *flag)
{
	char		c;

	*flag = 0;
	while (*s)
	{
		c = *s;
		if (c == '#')
			*flag |= PREFIX;
		else if (c == '0')
			*flag |= ZERO_PAD;
		else if (c == '-')
			*flag |= LEFT_ALIGN;
		else if (c == ' ')
			*flag |= BLANK_SIGN;
		else if (c == '+')
			*flag |= SHOW_SIGN;
		else
			return (s);
		++s;
	}
	return (s);
}

/*
	Get the minimum width (>= 0) out of the format and asign it to width.
	@return pointer of s after width.
*/
static const char	*set_width(const char *s, int *width)
{
	*width = 0;
	while (ft_isdigit(*s))
	{
		*width = *width * 10 + (*s - '0');
		++s;
	}
	return (s);
}

/*
	Helper function for getting the precision out of the format.
	Presicion -1 means no precision is set.
	@return pointer of s after precision.
*/
static const char	*set_precision(const char *s, int *precision)
{
	if (*s != '.')
	{
		*precision = -1;
		return (s);
	}
	*precision = 0;
	while (*(++s) && ft_isdigit(*s))
		*precision = *precision * 10 + (*s - '0');
	return (s);
}

/*
	Parse the given format into f.
	@return Pointer to s ending on the specificer.
*/
const char	*ft_parse_format(const char *s, t_format *f)
{
	s = set_flags(s, &f->flags);
	s = set_width(s, &f->width);
	return (set_precision(s, &f->precis));
}
