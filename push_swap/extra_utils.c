/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:39:30 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/12 12:01:17 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	my_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void	rotate_to_best_target(t_list **a, t_list **b, int best_target)
{
	int	cost_a;
	int	cost_b;

	cost_a = calculator_rotation_cost(*a, best_target);
	cost_b = calculator_rotation_cost(*b, best_target);
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
		cost_a = calculator_rotation_cost(*a, current->content);
		cost_b = calculator_rotation_cost(*b, current->content);
		if ((my_abs(cost_a) + my_abs(cost_b)) < min_cost)
		{
			min_cost = my_abs(cost_a) + my_abs(cost_b);
			best_target = current->content;
		}
		current = current->next;
	}
	rotate_to_best_target(a, b, best_target);
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
