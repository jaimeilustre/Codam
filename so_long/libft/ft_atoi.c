/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 14:52:59 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/10 15:33:44 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long		nb;

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
		nb = nb * 10 + (nptr[i] - '0');
		if (nb > INT_MAX && sign == 1)
			return (LONG_MAX);
		if (nb > (long)INT_MAX + 1 && sign == -1)
			return (LONG_MIN);
		i++;
	}
	return (nb * sign);
}
