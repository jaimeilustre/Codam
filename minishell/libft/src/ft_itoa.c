/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:50:47 by jboon             #+#    #+#             */
/*   Updated: 2024/11/29 15:48:29 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	count_digits(int n)
{
	size_t	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}

static void	fill_str_nbr(unsigned int n, size_t len, char *nbr, int is_negative)
{
	if (n == 0)
		nbr[len - 1] = '0';
	else if (is_negative)
		nbr[0] = '-';
	while (n != 0)
	{
		nbr[--len] = '0' + (n % 10);
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*nbr;

	len = count_digits(n) + (n < 0);
	nbr = malloc((len + 1) * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	nbr[len] = '\0';
	if (n < 0)
		fill_str_nbr((~n + 1), len, nbr, 1);
	else
		fill_str_nbr(n, len, nbr, 0);
	return (nbr);
}
