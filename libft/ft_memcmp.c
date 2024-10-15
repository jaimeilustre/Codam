/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:53:14 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/15 16:07:03 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*cs1;
	char	*cs2;

	cs1 = (const char *)s1;
	cs2 = (const char *)s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] < cs2[i])
			return (-1);
		else if (cs1[i] > cs2[i])
			return (1);
		i++;
	}
	return (0);
}
