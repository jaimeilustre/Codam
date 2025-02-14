/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:56:00 by jboon             #+#    #+#             */
/*   Updated: 2024/10/14 16:46:35 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	const size_t	max_size = sizeof(size_t);
	unsigned char	*s1;
	size_t			*s2;

	if (n >= max_size)
	{
		s2 = (size_t *)s;
		while (n >= max_size)
		{
			n -= max_size;
			*s2 = 0UL;
			++s2;
		}
		s = s2;
	}
	if (n > 0)
	{
		s1 = (unsigned char *)s;
		while (n > 0)
		{
			--n;
			*s1 = 0;
			++s1;
		}
	}
}
