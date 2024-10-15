/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:22:25 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/15 16:06:48 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(int nb)
{
	size_t	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	nb;
	char			*str;

	len = count_digits(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	else if (n < 0)
	{
		nb = -n;
		str[0] = '-';
	}
	else
		nb = n;
	while (nb != 0)
	{
		str[len--] = '0' + (nb % 10);
		nb = nb / 10;
	}
	return (str);
}
