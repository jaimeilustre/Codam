/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/21 13:11:54 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/21 16:04:50 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	free_args(list->items);
	free(list->flags);
	ft_bzero(list, sizeof(t_alist));
}
