/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:22:11 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/10 11:34:38 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strdup(const char *s)
{
	int		s_size;
	char	*dest;
	int		i;

	s_size = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * s_size + 1);
	i = 0;
	while (i <= s_size)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
