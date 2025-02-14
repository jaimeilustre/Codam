/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:23:51 by jboon             #+#    #+#             */
/*   Updated: 2024/10/29 12:49:07 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Count the amount of decimals in the given unsigned number.
*/
int	ft_count_digits(t_ulint nbr)
{
	int	count;

	if (nbr == 0)
		return (1);
	count = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		++count;
	}
	return (count);
}

/*
	Count the amount of power of two digits in the given unsinged number.
	@param pow Binary = 1, Quaternary = 2, Octal = 3, Hexadecimal = 4.
*/
int	ft_count_pow2(t_ulint nbr, int pow)
{
	int	count;

	if (nbr == 0)
		return (1);
	count = 0;
	while (nbr != 0)
	{
		nbr >>= pow;
		++count;
	}
	return (count);
}
