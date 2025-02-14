/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:12:56 by jboon             #+#    #+#             */
/*   Updated: 2024/10/29 15:01:50 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Initialize the data container for the uint printf function.
*/
static void	init_t_nbr(t_nbr *data, t_format *f, t_ulint nbr, bool is_minus)
{
	data->base = DECIMAL;
	data->nbr = nbr;
	data->is_minus = is_minus;
	data->nbr_cnt = ft_count_digits(nbr);
	data->pre = "";
	f->flags &= ~PREFIX;
	ft_printf_size(data, f, is_minus);
}

/*
	Convert n to string in decimal system.
*/
static void	ft_nbr_to_str(char *dst, t_nbr *data)
{
	t_ulint	n;
	int		count;

	n = data->nbr;
	count = data->nbr_cnt;
	while (count != 0)
	{
		--count;
		dst[count] = data->base[n % 10];
		n /= 10;
	}
}

/*
	Create and return a formatted string representation of nbr as an unsigned
	integer.
	@param nbr The original nbr.
	@param f The format to apply on the nbr.
	@param is_minus is the number perceived as an negative.
	@param str_len Length of the formatted string.
*/
char	*ft_printf_uint(t_ulint nbr, t_format *f, bool is_minus, int *str_len)
{
	char	*dst;
	t_nbr	nbr_data;

	init_t_nbr(&nbr_data, f, nbr, is_minus);
	if (ft_empty_str(&dst, nbr_data.str_len) == false)
		return (dst);
	if (nbr_data.str_len)
	{
		if ((f->flags & LEFT_ALIGN) != 0)
			left_align_nbr(dst, f, &nbr_data, ft_nbr_to_str);
		else
			right_align_nbr(dst, f, &nbr_data, ft_nbr_to_str);
	}
	*str_len = nbr_data.str_len;
	return (dst);
}
