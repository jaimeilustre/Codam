/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:57:17 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/15 16:08:21 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;
	
	dest = (char *)malloc(sizeof(*s) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			dest[j] = s[i];
			j++; 			
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "Hello, world!";

// 	printf("%s\n", ft_substr(str, 5, 13));
// 	return (0);
// }
