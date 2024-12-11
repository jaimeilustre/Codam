/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chunk_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:51:39 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/11 12:32:34 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void rotate_to_top(t_list **a, int index)
{
    int size = ft_lstsize(*a);

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

int has_target_in_chunk(t_list *a, int chunk_min, int chunk_max)
{
    while (a)
    {
        if (a->content >= chunk_min && a->content <= chunk_max)
            return (1);
        a = a->next;
    }
    return (0);
}

int find_closest(t_list *a, int chunk_min, int chunk_max)
{
    int index = 0;
    int closest_index = -1;
    int smallest_distance = INT_MAX;
    int size = ft_lstsize(a);
    t_list *current = a;

    while (current)
    {
        if (current->content >= chunk_min && current->content <= chunk_max)
        {
            int distance = index < (size - index) ? index : (size - index);
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

void create_chunks(t_list **a, t_list **b, int total_elements, int **chunks, int *chunk_count)
{
    int chunk_size = total_elements / 10;
    int current_min;
    int current_max;
    int i = 0;

    *chunks = malloc(sizeof(int) * (10 + 1));
    if (!*chunks)
        exit_error(NULL, NULL, NULL);

    while (*a)
    {
        current_min = find_min(*a);
        current_max = current_min + chunk_size;
        (*chunks)[i++] = current_max;
        while (has_target_in_chunk(*a, current_min, current_max))
        {
            rotate_to_top(a, find_closest(*a, current_min, current_max));
            pb(a, b);
        }
    }
    (*chunks)[i] = INT_MAX;
    *chunk_count = i;
}

void	push_min_cost_element(t_list **a, t_list **b)
{
	t_list	*current;
	int		min_cost;
	int		best_target;
	int		cost_a;
	int		cost_b;
	int		total_cost;

	current = *a;
	min_cost = INT_MAX;
	while (current)
	{
		cost_a = calculator_rotation_cost(*a, current->content);
		cost_b = calculator_rotation_cost(*b, current->content);
		total_cost = abs(cost_a) + abs(cost_b);
		if (total_cost < min_cost)
		{
			min_cost = total_cost;
			best_target = current->content;
		}
		current = current->next;
	}
	while ((*a)->content != best_target)
	{
		if (cost_a > 0 && cost_b > 0)
    		rr(a, b);
        else if (cost_a < 0 && cost_b < 0)
            rrr(a, b);
        else if (cost_a > 0)
            ra(a);
        else
            rra(a);
	}
	pb(a, b);
}

void	push_to_b(t_list **a, t_list **b, int chunk_min, int chunk_max)
{
	t_list	*current;
	int		has_target;
	
	while (*a)
	{
		current = *a;
		has_target = 0;
		while (current)
		{
			if (current->content >= chunk_min && current->content <= chunk_max)
			{
				has_target = 1;
				break ;
			}
			current = current->next;
		}
		if (!has_target)
			break ;
		push_min_cost_element(a, b);
		if (*b && (*b)->next && (*b)->content < (*b)->next->content)
			sb(b);
	}
}

void	sort_b_to_a(t_list **a, t_list **b)
{
	int	max;
	int	rotation;
	
	while (*b)
	{
		max = find_max(*b);
		rotation = calculator_rotation_cost(*b, max);
		while ((*b)->content != max)
		{
			if (rotation > 0)
				rb(b);
			else
				rrb(b);
		}
		pa(a, b);
	}
}
