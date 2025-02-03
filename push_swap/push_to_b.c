/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_to_b.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:39:30 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/03 21:10:57 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int	find_max(t_list *stack)
{
	int	max;

	max = INT_MIN;
	while (stack)
	{
		if (stack->content > max)
			max = stack->content;
		stack = stack->next;
	}
	return (max);
}

int	calculate_rotation_cost(t_list *stack, int target)
{
	int		forward_steps;
	int		reverse_steps;
	int		total_size;
	t_list	*current;

	forward_steps = 0;
	current = stack;
	while (current && current->content != target)
	{
		forward_steps++;
		current = current->next;
	}
	total_size = ft_lstsize(stack);
	reverse_steps = total_size - forward_steps;
	if (forward_steps <= reverse_steps)
		return (forward_steps);
	else
		return (-reverse_steps);
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
