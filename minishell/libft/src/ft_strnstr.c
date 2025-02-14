/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:09:16 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 13:35:36 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*curr;
	const char	*end;

	if (*needle == '\0')
		return ((char *)haystack);
	if (len > SIZE_MAX - (size_t)haystack)
		end = haystack + SIZE_MAX - (size_t)haystack;
	else
		end = haystack + len;
	while (haystack < end && *haystack)
	{
		curr = haystack;
		while (*curr && curr < end && *curr == *needle)
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
