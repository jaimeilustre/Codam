/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:00 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/10 10:34:40 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	total_len;
	unsigned int	i;

	dest_len = 0;
	src_len = 0;
	total_len = 0;
	i = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	while (src[src_len])
		src_len++;
	total_len = dest_len + src_len;
	if (size == 0 || dest_len >= size)
		return (total_len);
	while (src[i] && (dest_len + i) < (size - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (total_len);
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
