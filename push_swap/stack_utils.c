/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:49:37 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/10 14:12:42 by jilustre      ########   odam.nl         */
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

int	find_min(t_list *stack)
{
	int	min;
	
	if (!stack)
		return (INT_MAX);
	min = INT_MAX;
	while (stack)
	{
		if (stack->content < min)
			min = stack->content;
		stack = stack->next;
	}
	return (min);
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

int	calculator_rotation_cost(t_list *stack, int target)
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