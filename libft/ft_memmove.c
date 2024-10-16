/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:24 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 07:30:07 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*cdest;
	char	*csrc;
	char	*temp;
	
	if (dest == src || n == 0)
		return (dest);
	temp = (char *)malloc(n);
	if (!temp)
		return (NULL);
	cdest = (char *)dest;
	csrc = (char *)src;
	i = 0;
	while (i < n)
	{
		temp[i] = csrc[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		cdest[i] = temp[i];
		i++;
	}
	free (temp);
	return (dest);
}
