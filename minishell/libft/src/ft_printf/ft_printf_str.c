/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:09:45 by jboon             #+#    #+#             */
/*   Updated: 2024/12/03 15:33:25 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

/*
	Check if src is NULL and return "(null)" string with adjusted formatted
	options. If not null, return src.
*/
static char	*process_string(char *src, size_t *len, t_format *f)
{
	if (src == NULL)
	{
		*len = ft_strlen("(null)");
		if (f->precis != -1 && (size_t)f->precis < *len)
			*len = 0;
		return ("(null)");
	}
	*len = ft_strlen(src);
	return (src);
}

/*
	Allocate len + 1 bytes for dst and set all characters to \s.
	@return On success will return true and false if malloc fails.
*/
bool	ft_empty_str(char **dst, int str_len)
{
	*dst = malloc((str_len + 1) * sizeof(char));
	if (*dst == NULL)
		return (false);
	*dst = ft_memset(*dst, ' ', str_len);
	*(*dst + str_len) = '\0';
	return (true);
}

/*
	Create and return a formatted string based on src.
	@param src The original string.
	@param f The format to apply on the src.
	@param str_len Length of the formatted string.
*/
char	*ft_printf_str(char *src, t_format *f, int *str_len)
{
	size_t	sub_len;
	size_t	full_len;
	char	*dst;

	src = process_string(src, &sub_len, f);
	if (f->precis >= 0 && f->precis < (int)sub_len)
		sub_len = f->precis;
	if (f->width > (int)sub_len)
		full_len = f->width;
	else
		full_len = sub_len;
	if (ft_empty_str(&dst, full_len) == false)
		return (dst);
	if ((f->flags & LEFT_ALIGN) != 0)
		ft_memcpy(dst, src, sub_len);
	else
		ft_memcpy(dst + (full_len - sub_len), src, sub_len);
	*str_len = (int)full_len;
	return (dst);
}
