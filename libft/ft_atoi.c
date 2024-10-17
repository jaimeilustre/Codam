/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:52:59 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/17 07:42:56 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(long nb, int sign, char next_digit)
{
	if (nb > (LONG_MAX - (next_digit - '0')) / 10)
	{
		if (sign == 1)
			return (INT_MAX);
		else
			return (INT_MIN);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	nb;
	int		overflow;

	nb = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		overflow = check_overflow(nb, sign, nptr[i]);
		if (overflow != 0)
			return (overflow);
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(nb * sign));
}
