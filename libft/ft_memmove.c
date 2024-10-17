/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:24 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 19:45:15 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	if (dest == src || n == 0)
		return (dest);
	if (((char *)dest) > ((const char *)src))
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((const char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((const char *)src)[i];
			i++;
		}	
	}
	return (dest);
}

// #include <stdio.h>

// int main(void)
// {
// 	char src[50] = "Hello, this is a memmove test.";
// 	char dest[50];

// 	// Test 1: Non-overlapping memory
// 	printf("Test 1: Non-overlapping\n");
// 	printf("Source before memmove: %s\n", src);
// 	ft_memmove(dest, src, ft_strlen(src) + 1);  // +1 to include null terminator
// 	printf("Destination after memmove: %s\n\n", dest);

// 	// Test 2: Overlapping memory (src within dest)
// 	printf("Test 2: Overlapping (src within dest)\n");
// 	char overlap[50] = "1234567890";
// 	printf("Overlap before memmove: %s\n", overlap);
// 	ft_memmove(overlap + 4, overlap, 6);  // Intentionally overlapping regions
// 	printf("Overlap after memmove: %s\n\n", overlap);

// 	// Test 3: Overlapping memory (dest before src)
// 	printf("Test 3: Overlapping (dest before src)\n");
// 	char overlap2[50] = "ABCDEFGHIJK";
// 	printf("Overlap2 before memmove: %s\n", overlap2);
// 	ft_memmove(overlap2, overlap2 + 4, 7);  // Another overlap but dest < src
// 	printf("Overlap2 after memmove: %s\n", overlap2);

// 	return 0;
// }
