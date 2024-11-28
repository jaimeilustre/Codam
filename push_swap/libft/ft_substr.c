/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:57:17 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 10:11:08 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	substr_len = s_len - start;
	if (substr_len > len)
		substr_len = len;
	substr = (char *)malloc(sizeof(*s) * (substr_len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}
