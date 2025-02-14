/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:52:54 by jboon             #+#    #+#             */
/*   Updated: 2024/10/14 10:59:36 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*mem;
	unsigned char		character;

	i = 0;
	mem = (unsigned char *)s;
	character = (unsigned char)c;
	while (i < n)
	{
		if (mem[i] == character)
			return ((void *)(mem + i));
		++i;
	}
	return (NULL);
}
