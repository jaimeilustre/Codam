/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:34:34 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 11:28:15 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = 0;
	dst_len = 0;
	while (dst[dst_len] && dst_len < size)
		++dst_len;
	if (dst_len < size)
	{
		while (src[src_len] && (dst_len + src_len) < (size - 1))
		{
			dst[dst_len + src_len] = src[src_len];
			++src_len;
		}
		dst[dst_len + src_len] = '\0';
	}
	while (src[src_len])
		++src_len;
	return (dst_len + src_len);
}
