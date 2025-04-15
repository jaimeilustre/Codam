/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stringbuilder.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 13:08:25 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/13 10:49:59 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"
#include "ms_string.h"

static bool	expand_strb(t_strb *sb, size_t min_cap)
{
	t_str	prev_str;
	size_t	curr_size;
	size_t	max_cap;

	max_cap = sb->capacity * 2;
	if (min_cap > max_cap)
		max_cap = min_cap;
	prev_str = sb->str;
	curr_size = sb->size;
	if (!init_strb(sb, max_cap))
	{
		sb->str = prev_str;
		return (false);
	}
	ft_memcpy(sb->str, prev_str, curr_size + 1);
	sb->size = curr_size;
	free(prev_str);
	return (true);
}

bool	init_strb(t_strb *sb, size_t capacity)
{
	if (capacity < 1)
		capacity = 512;
	sb->str = ft_calloc(capacity + 1, sizeof(char));
	if (sb->str == NULL)
		return (false);
	sb->size = 0;
	sb->capacity = capacity;
	return (true);
}

void	free_strb(t_strb *sb)
{
	free(sb->str);
	sb->str = NULL;
	sb->size = 0;
	sb->capacity = 0;
}

bool	append_strb(t_strb *sb, t_cstr src, size_t len)
{
	if (len > 0)
	{
		if (sb->str == NULL)
		{
			if (!init_strb(sb, len))
				return (false);
		}
		else if (sb->capacity < (sb->size + len)
			&& !expand_strb(sb, (sb->size + len)))
			return (false);
		ft_memcpy((sb->str + sb->size), src, len);
		sb->size += len;
		sb->str[sb->size] = '\0';
	}
	return (true);
}

bool	shrink_strb(t_strb *sb)
{
	t_str	prev_str;
	size_t	prev_size;
	size_t	prev_capacity;

	if (sb->size == sb->capacity || sb->size == 0)
		return (true);
	prev_str = sb->str;
	prev_size = sb->size;
	prev_capacity = sb->capacity;
	if (!init_strb(sb, prev_size) || !append_strb(sb, prev_str, prev_size))
	{
		free(sb->str);
		sb->size = prev_size;
		sb->capacity = prev_capacity;
		sb->str = prev_str;
		sb->str = prev_str;
		return (false);
	}
	free(prev_str);
	return (true);
}
