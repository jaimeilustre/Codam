/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:23:03 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 17:38:56 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	if (s != NULL)
	{
		while (*s)
		{
			while (*s == c)
				++s;
			if (*s != '\0')
				++count;
			while (*s != c && *s)
				++s;
		}
	}
	return (count);
}

static char	**free_words(char **words, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(words[i]);
		++i;
	}
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	word_len;
	char	**words;

	count = count_words(s, c);
	words = malloc((count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	i = 0;
	words[count] = NULL;
	while (i < count)
	{
		while (*s == c)
			++s;
		word_len = 0;
		while (s[word_len] != c && s[word_len])
			++word_len;
		words[i] = ft_substr(s, 0, word_len);
		if (words[i] == NULL)
			return (free_words(words, i + 1));
		s += word_len;
		++i;
	}
	return (words);
}
