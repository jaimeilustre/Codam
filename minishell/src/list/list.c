/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 18:03:53 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/14 17:03:14 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "list.h"

bool	init_list(t_alist *list, int capacity)
{
	capacity += (capacity == 0);
	list->items = ft_calloc(capacity + 1, sizeof(t_str));
	if (list->items == NULL)
		return (false);
	list->size = 0;
	list->capacity = capacity;
	return (true);
}

int	find_item_in_list(t_alist *list, t_cstr item, t_compare comp)
{
	int	i;

	i = 0;
	while (i < list->size)
	{
		if (comp(list->items[i], item) == 0)
			return (i);
		++i;
	}
	return (-1);
}

void	sort_list(t_alist *list, t_compare comp)
{
	int		i;
	int		j;
	int		min;

	i = 0;
	while (i < list->size)
	{
		min = i;
		j = i + 1;
		while (j < list->size)
		{
			if (comp(list->items[j], list->items[min]) < 0)
				min = j;
			++j;
		}
		swap_ptr((void **)(&list->items[min]), (void **)(&list->items[i]));
		++i;
	}
}
