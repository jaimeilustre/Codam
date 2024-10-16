/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:00 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 07:38:01 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0 || dst_len >= size)
		return (dst_len + src_len);
	i = 0;
	while (src[i] && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	dest[12] = "Hello,";
// 	char	*src = " world!";
// 	char	result = ft_strlcat(dest, src, 20);

// 	printf("String: %s\n", dest);
// 	printf("Total length of string: %hhd\n", result);
// 	return (0);
// }
