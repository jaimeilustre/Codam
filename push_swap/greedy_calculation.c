/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   greedy_calculation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:39:30 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/16 16:40:35 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_to_best_target(t_list **a, t_list **b, int best_target)
{
	int	cost_a;
	int	cost_b;

	cost_a = calculate_rotation_cost(*a, best_target);
	cost_b = calculate_rotation_cost(*b, best_target);
	while ((*a)->content != best_target)
	{
		if (cost_a > 0 && cost_b > 0)
			rr(a, b, 1);
		else if (cost_a < 0 && cost_b < 0)
			rrr(a, b, 1);
		else if (cost_a > 0)
			ra(a, 1);
		else
			rra(a, 1);
	}
}

void	push_min_cost_element(t_list **a, t_list **b)
{
	t_list	*current;
	int		min_cost;
	int		best_target;
	int		cost_a;
	int		cost_b;

	current = *a;
	min_cost = INT_MAX;
	while (current)
	{
		cost_a = calculate_rotation_cost(*a, current->content);
		cost_b = calculate_rotation_cost(*b, current->content);
		if ((cost_a + cost_b) < min_cost)
		{
			min_cost = cost_a + cost_b;
			best_target = current->content;
		}
		current = current->next;
	}
	rotate_to_best_target(a, b, best_target);
	pb(a, b, 1);
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
			sb(b, 1);
	}
}

void	sort_b_to_a(t_list **a, t_list **b)
{
	int	max;
	int	rotation;

	while (*b)
	{
		max = find_max(*b);
		rotation = calculate_rotation_cost(*b, max);
		while ((*b)->content != max)
		{
			if (rotation > 0)
				rb(b, 1);
			else
				rrb(b, 1);
		}
		pa(a, b, 1);
	}
}
