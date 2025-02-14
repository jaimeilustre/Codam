/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:27:21 by jboon             #+#    #+#             */
/*   Updated: 2024/10/29 13:57:53 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Initialize the data container for the hex printf function.
*/
static void	init_t_nbr(t_nbr *data, t_format *f, t_ulint nbr, bool use_up)
{
	data->nbr = nbr;
	data->nbr_cnt = ft_count_pow2(nbr, 4);
	data->is_minus = 0;
	if (use_up)
	{
		data->base = HEX_UPPER;
		data->pre = "0X";
	}
	else
	{
		data->base = HEX_LOWER;
		data->pre = "0x";
	}
	ft_printf_size(data, f, false);
}

/*
	Convert the nbr to the hexidecimal system.
 */
static void	ft_nbr_to_hex(char *dst, t_nbr *data)
{
	t_ulint	n;
	int		count;

	n = data->nbr;
	count = data->nbr_cnt;
	while (count != 0)
	{
		--count;
		dst[count] = data->base[n & 0xf];
		n >>= 4;
	}
}

/*
	Create and return a formatted hex string representation of nbr.
	@param nbr The original nbr that will be converted to hex.
	@param f The format to apply on the nbr.
	@param str_len Length of the formatted string.
	@param use_up Whether to use the lower or upper case version of hexadecimal.
*/
char	*ft_printf_hex(t_ulint nbr, t_format *f, bool use_up, int *str_len)
{
	char	*dst;
	t_nbr	data;

	init_t_nbr(&data, f, nbr, use_up);
	if (ft_empty_str(&dst, data.str_len) == false)
		return (dst);
	if (data.str_len)
	{
		if ((f->flags & LEFT_ALIGN) != 0)
			left_align_nbr(dst, f, &data, ft_nbr_to_hex);
		else
			right_align_nbr(dst, f, &data, ft_nbr_to_hex);
	}
	*str_len = data.str_len;
	return (dst);
}
