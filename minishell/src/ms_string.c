/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_string.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 14:47:05 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/20 12:39:10 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "ms_string.h"

bool	is_empty_cmd(t_cstr str)
{
	while (*str != '\0' && *str != '#'
		&& (*str == ' ' || *str == '\t' || *str == '\\'))
		++str;
	return (*str == '\0' || *str == '#');
}

size_t	count_args(t_str *words)
{
	t_str	*start;

	start = words;
	while (*words)
		++words;
	return (words - start);
}

void	free_args(t_str *words)
{
	t_str	*tmp;

	tmp = words;
	while (*tmp != NULL)
	{
		free(*tmp);
		++tmp;
	}
	free(words);
	words = NULL;
}

void	append_to_path(t_str full_path, t_cstr path, t_cstr cmd)
{
	ft_strlcat(full_path, path, PATH_MAX);
	ft_strlcat(full_path, "/", PATH_MAX);
	ft_strlcat(full_path, cmd, PATH_MAX);
}

int	ft_strcmp(t_cstr s1, t_cstr s2)
{
	while (*s1 == *s2 && *s1)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
