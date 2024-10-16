/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:30:53 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 13:19:34 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

static char	*allocate_word(char const **s, char c)
{
	char	*next;
	char	*word;

	next = ft_strchr(*s, c);
	if (!next)
		next = *s + ft_strlen(*s);
	word = (char *)malloc(next - *s + 1);
	if (word)
	{
		ft_strlcpy(word, *s, next - *s + 1);
		*s = next;
	}
	return (word);
}

static void	free_split(char **strs, size_t count)
{
	while (count > 0)
		free(strs[--count]);
	free (strs);
}

static char	*allocate_and_free(const char **s, char c, size_t *i, char **strs)
{
	strs[*i] = allocate_word(s, c);
	if (!strs[*i])
	{
		free_split(strs, *i);
		return (NULL);
	}
	(*i)++;
	return (strs[*i - 1]);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!allocate_and_free(&s, c, &i, strs))
				return (NULL);
		}
	}
	strs[i] = NULL;
	return (strs);
}
