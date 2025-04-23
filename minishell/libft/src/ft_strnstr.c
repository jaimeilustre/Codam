/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 18:09:16 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/02 22:31:19 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*curr;

	if (*needle == '\0')
		return ((char *)haystack);
	while (len > 0 && *haystack)
	{
		curr = haystack;
		while (len > 0 && *curr && *curr == *needle)
		{
			--len;
			++curr;
			++needle;
		}
		if (*needle == '\0')
			return ((char *)haystack);
		needle -= (curr - haystack);
		len += (curr - haystack) - 1;
		++haystack;
	}
	return (NULL);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*curr;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		curr = haystack;
		while (*curr && *curr == *needle)
		{
			++curr;
			++needle;
		}
		if (*needle == '\0')
			return ((char *)haystack);
		needle -= (curr - haystack);
		++haystack;
	}
	return (NULL);
}

char	*ft_strrstr(const char *haystack, const char *needle)
{
	const char	*curr;
	const char	*last;

	if (*needle == '\0')
		return ((char *)haystack);
	last = NULL;
	while (*haystack)
	{
		curr = haystack;
		while (*curr && *curr == *needle)
		{
			++curr;
			++needle;
		}
		if (*needle == '\0')
			last = haystack;
		needle -= (curr - haystack);
		++haystack;
	}
	return ((char *)last);
}
