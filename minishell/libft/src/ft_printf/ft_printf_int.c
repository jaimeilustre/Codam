/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:13:22 by jboon             #+#    #+#             */
/*   Updated: 2024/12/03 10:43:11 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Create and return a formatted string representation of nbr as an integer.
	@param nbr The original nbr.
	@param f The format to apply on the nbr.
	@param str_len Length of the formatted string.
*/
char	*ft_printf_int(int nbr, t_format *f, int *str_len)
{
	if (nbr < 0)
		return (ft_printf_uint((t_ulint) ~ nbr + 1, f, true, str_len));
	else
		return (ft_printf_uint(nbr, f, false, str_len));
}
