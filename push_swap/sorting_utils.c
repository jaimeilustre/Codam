/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sorting_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:57:04 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/13 10:58:12 by jilustre      ########   odam.nl         */
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
			ra(a);
	}
	else
	{
		index = size - index;
		while (index--)
			rra(a);
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
	t_list	*current;

	index = 0;
	closest_index = -1;
	smallest_distance = INT_MAX;
	current = a;
	while (current)
	{
		if (current->content >= chunk_min && current->content <= chunk_max)
		{
			distance = calculate_distance(index, ft_lstsize(a));
			if (distance < smallest_distance)
			{
				smallest_distance = distance;
				closest_index = index;
			}
		}
		current = current->next;
		index++;
	}
	return (closest_index);
}