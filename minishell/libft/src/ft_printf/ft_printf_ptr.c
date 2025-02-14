/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:16:51 by jboon             #+#    #+#             */
/*   Updated: 2024/10/29 14:04:05 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"

/*
	Create and return a formatted hex string representation of the ptr address.
	@param ptr The original ptr that will be converted to hex.
	@param f The format to apply on the nbr.
	@param str_len Length of the formatted string.
	@param use_up Whether to use the lower or upper case version of hexadecimal.
*/
char	*ft_printf_ptr(void *ptr, t_format *f, int *str_len)
{
	if (ptr == NULL)
	{
		f->precis = -1;
		return (ft_printf_str("(nil)", f, str_len));
	}
	f->flags |= PREFIX;
	return (ft_printf_hex((uintptr_t)ptr, f, false, str_len));
}
