/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:22:25 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/17 08:43:57 by jilustre         ###   ########.fr       */
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

static void	fill_string(char *str, unsigned int nb, int len)
{
	while (nb != 0)
	{
		str[len--] = '0' + (nb % 10);
		nb = nb / 10;
	}
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
		str[0] = '0';
	else if (n == INT_MIN)
		ft_strlcpy(str, "-2147483648", len + 2);
	else
	{
		if (n < 0)
		{
			nb = -n;
			str[0] = '-';
		}
		else
			nb = n;
		fill_string(str, nb, len);
	}
	return (str);
}
