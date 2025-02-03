/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chunk_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:57:04 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/03 15:39:26 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_to_top(t_list **a, int index)
{
	int	size;

	size = ft_lstsize(*a);
	if (index <= size / 2)
	{
		while (index--)
			ra(a, 1);
	}
	else
	{
		index = size - index;
		while (index--)
			rra(a, 1);
	}
}

int	has_target_in_chunk(t_list *a, int chunk_min, int chunk_max)
{
	while (a)
	{
		if (a->content >= chunk_min && a->content <= chunk_max)
			return (1);
		a = a->next;
	}
	return (0);
}

int	calculate_distance(int index, int size)
{
	if (index < size - index)
		return (index);
	else
		return (size - index);
}

int	find_closest(t_list *a, int chunk_min, int chunk_max)
{
	int		index;
	int		closest_index;
	int		smallest_distance;
	int		distance;
	int		size;

	index = 0;
	closest_index = -1;
	smallest_distance = INT_MAX;
	size = ft_lstsize(a);
	while (a)
	{
		if (a->content >= chunk_min && a->content <= chunk_max)
		{
			distance = calculate_distance(index, size);
			if (distance < smallest_distance)
			{
				smallest_distance = distance;
				closest_index = index;
			}
		}
		a = a->next;
		index++;
	}
	return (closest_index);
}
