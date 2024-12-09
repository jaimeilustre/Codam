/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chunk_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:51:39 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/09 16:32:27 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	create_chunks(int total_elements, int **chunks, int *chunk_count)
{
	int	chunk_size;
	int	i;

	if (total_elements < 100)
		chunk_size = 5;
	else
		chunk_size = total_elements / 20;
	*chunks = malloc(sizeof(int) * ((total_elements / chunk_size) + 1));
	if (!*chunks)
		exit_error(NULL, NULL, NULL);
	i = 0;
	while (i <= total_elements / chunk_size)
	{
		(*chunks)[i] = i * chunk_size;
		i++;
	}
	*chunk_count = i;
	
	// int base_chunk_size = total_elements / 20;
    // int extra_chunks = total_elements % 20;
    // int i = 0;

	// if (total_elements <= 20) {
    //     base_chunk_size = 1;
    //     *chunks = malloc(sizeof(int) * total_elements);
    //     if (!*chunks)
    //         exit_error(NULL, NULL, NULL);
    //     for (i = 0; i < total_elements; i++)
    //         (*chunks)[i] = i + 1;
    //     *chunk_count = total_elements;
    //     return;
    // }

    // *chunks = malloc(sizeof(int) * (20 + (extra_chunks > 0 ? 1 : 0)));
    // if (!*chunks)
    //     exit_error(NULL, NULL, NULL);

    // while (i < 20) 
	// {
    //     (*chunks)[i] = base_chunk_size * (i + 1);
    //     i++;
    // }

    // if (extra_chunks > 0)
    //     (*chunks)[i++] = total_elements;  // Add final chunk boundary for remaining elements.
    // *chunk_count = i;
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
		// cost_a = calculator_rotation_cost(*a, current->content);
		// cost_b = calculator_rotation_cost(*b, current->content);
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
