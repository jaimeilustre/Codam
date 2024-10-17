/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:30:53 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 21:16:56 by jaimeilustr      ###   ########.fr       */
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

static void	split_words(const char *str, char sep, char **result)
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
				free(result);
				return ;
			}
			i++;
		}
	}
	result[i] = NULL;
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
	split_words(s, c, result);
	return (result);
}

// #include <stdio.h>

// int main(void)
// {
//     char **result = ft_split("Hello world, this is a test.", ' ');

//     if (result)
//     {
//         for (int i = 0; result[i] != NULL; i++)
//         {
//             printf("Word %d: %s\n", i + 1, result[i]);
//             free(result[i]);
//         }
//         free(result);
//     }
//     return 0;
// }
