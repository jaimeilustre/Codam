/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/21 13:11:54 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:56:18 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "list.h"

bool	init_list(t_alist *list, int capacity)
{
	capacity += (capacity == 0);
	list->items = ft_calloc(capacity + 1, sizeof(t_str));
	list->flags = ft_calloc(capacity + 1, sizeof(int));
	if (list->items == NULL || list->flags == NULL)
	{
		free(list->items);
		free(list->flags);
		list->items = NULL;
		list->flags = NULL;
		return (false);
	}
	list->size = 0;
	list->capacity = capacity;
	return (true);
}

void	free_list(t_alist *list)
{
	if (list->items != NULL)
		free_args(list->items);
	free(list->flags);
	ft_bzero(list, sizeof(t_alist));
}

/* Same as free_list but doesn't free the individual items */
void	shallow_free_list(t_alist *list)
{
	free(list->items);
	free(list->flags);
	ft_bzero(list, sizeof(t_alist));
}

/* Retain the capacity and mallocs but free each item and set to NULL */
void	clear_list(t_alist *list)
{
	t_str	*args;

	args = list->items;
	while (*args)
	{
		free(*args);
		*args = NULL;
		++args;
	}
	ft_bzero(list->flags, list->size * sizeof(t_env_fl));
	list->size = 0;
}
