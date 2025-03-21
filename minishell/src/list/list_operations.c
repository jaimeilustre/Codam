/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 15:24:42 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/14 15:25:34 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

static bool	expand_list(t_alist *list);

static bool	insert_items_into_list(t_alist *list, t_str *items)
{
	while (*items && list->size < list->capacity)
	{
		list->items[list->size] = *items;
		++list->size;
		++items;
	}
	return (true);
}

static bool	expand_list(t_alist *list)
{
	t_str	*old;

	old = list->items;
	if (init_list(list, list->capacity * 2) == false)
	{
		list->items = old;
		return (false);
	}
	insert_items_into_list(list, old);
	free (old);
	return (true);
}

bool	add_to_list(t_alist *list, t_str item)
{
	if (list->size == list->capacity && expand_list(list) == false)
		return (false);
	list->items[list->size] = item;
	++list->size;
	return (true);
}

bool	remove_index_from_list(t_alist *list, int i)
{
	if (i < 0 || i >= list->size)
		return (false);
	free(list->items[i]);
	list->size = i;
	insert_items_into_list(list, (list->items + i + 1));
	list->items[list->size] = NULL;
	return (true);
}
