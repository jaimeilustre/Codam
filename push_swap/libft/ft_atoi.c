/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 14:52:59 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/08 16:47:16 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	nb;

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
		if (nb > INT_MAX)
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		i++;
	}
	return ((int)(nb * sign));
}
