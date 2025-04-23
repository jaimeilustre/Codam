/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 16:58:25 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/03 14:07:37 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	if (size > 0)
	{
		while (src[len] && len < (size - 1))
		{
			dst[len] = src[len];
			++len;
		}
		dst[len] = '\0';
	}
	while (src[len])
		++len;
	return (len);
}

char	*ft_strcpy(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	while (*src)
	{
		*dst = *src;
		++dst;
		++src;
	}
	*dst = *src;
	return (ptr);
}
