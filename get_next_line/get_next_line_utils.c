/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 11:31:56 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/05 13:19:24 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(s1);
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	substr_len = s_len - start;
	if (substr_len > len)
		substr_len = len;
	substr = malloc(substr_len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < substr_len && (start + i) < s_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t		s_size;
	char		*dest;
	size_t		i;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (s_size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < s_size)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
