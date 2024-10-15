/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:53:11 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/15 16:06:56 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (i < n)
	{
		if (*(unsigned char*)(s + i) == (unsigned char)c)
			return ((void*)(s + i));
		i++;
	}
	return (NULL);
}
