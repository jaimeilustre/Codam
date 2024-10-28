/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:30:53 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/18 06:42:23 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char sep)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == sep)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*allocate_word(const char *start, const char *end)
{
	char	*word;
	size_t	i;
	size_t	len;

	len = end - start;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = *start++;
	word[i] = '\0';
	return (word);
}

static int	split_words(const char *str, char sep, char **result)
{
	size_t		i;
	const char	*word_start;

	i = 0;
	while (*str)
	{
		if (*str == sep)
			str++;
		else
		{
			word_start = str;
			while (*str && *str != sep)
				str++;
			result[i] = allocate_word(word_start, str);
			if (!result[i])
			{
				while (i > 0)
					free(result[--i]);
				return (free(result), -1);
			}
			i++;
		}
	}
	result[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	if (split_words(s, c, result) == -1)
		return (NULL);
	return (result);
}
