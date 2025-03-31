/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 18:03:53 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/21 16:08:43 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "list.h"

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
		swapi((int *)&list->flags[min], (int *)&list->flags[i]);
		++i;
	}
}

void	iter_list(t_alist *list, void (*f)(t_cstr, t_env_fl))
{
	int	i;

	i = 0;
	while (i < list->size)
	{
		f(list->items[i], list->flags[i]);
		++i;
	}
}

/* Create a (shallow) duplicate of src with items that match the filter */
bool	duplicate_list(t_alist *dst, t_alist *src, t_env_fl in, t_env_fl ex)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < src->size)
	{
		if ((src->flags[i] & in) != 0 && (src->flags[i] & ex) == 0)
			count++;
		++i;
	}
	if (!init_list(dst, count + 1))
		return (false);
	i = 0;
	while (i < src->size)
	{
		if ((src->flags[i] & in) != 0 && (src->flags[i] & ex) == 0)
			add_to_list(dst, src->items[i], src->flags[i]);
		++i;
	}
	return (true);
}
