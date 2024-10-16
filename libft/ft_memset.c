/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:26 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 07:14:54 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*cs;

	if (!s && n > 0)
		return (NULL);
	cs = (char *)s;
	i = 0;
	while (i < n)
	{
		cs[i] = c;
		i++;
	}
	return (s);
}
