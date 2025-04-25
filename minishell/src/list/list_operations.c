/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 15:24:42 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:15:59 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "list.h"

static bool	expand_list(t_alist *list);

static void	add_items_to_list(t_alist *list, t_str *items, t_env_fl *flags)
{
	while (*items && list->size < list->capacity)
	{
		list->items[list->size] = *items;
		list->flags[list->size] = *flags;
		++list->size;
		++flags;
		++items;
	}
}

static bool	expand_list(t_alist *list)
{
	t_str		*items;
	t_env_fl	*flags;

	items = list->items;
	flags = list->flags;
	if (init_list(list, list->capacity * 2) == false)
	{
		list->items = items;
		list->flags = flags;
		return (false);
	}
	add_items_to_list(list, items, flags);
	free (items);
	free (flags);
	return (true);
}

bool	add_to_list(t_alist *list, t_str item, t_env_fl flag)
{
	if (list->size == list->capacity && expand_list(list) == false)
		return (false);
	list->items[list->size] = item;
	list->flags[list->size] = flag;
	++list->size;
	return (true);
}

bool	remove_index_from_list(t_alist *list, int i)
{
	if (i < 0 || i >= list->size)
		return (false);
	free(list->items[i]);
	list->size = i;
	add_items_to_list(list, (list->items + i + 1), (list->flags + i + 1));
	list->items[list->size] = NULL;
	list->flags[list->size] = 0;
	return (true);
}
