/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:07:13 by jboon             #+#    #+#             */
/*   Updated: 2024/10/29 11:53:10 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Create and return a formatted string based on c.
	@param c The original character.
	@param f The format to apply on c.
	@param str_len Length of the formatted string.
*/
char	*ft_printf_char(char c, t_format *f, int *str_len)
{
	char	*str;

	if (f->width > 1)
		*str_len = f->width;
	else
		*str_len = 1;
	if (ft_empty_str(&str, *str_len) == false)
		return (str);
	if ((f->flags & LEFT_ALIGN) != 0)
		*str = c;
	else
		*(str + (*str_len - 1)) = c;
	return (str);
}
