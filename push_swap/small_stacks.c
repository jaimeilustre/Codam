/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   small_stacks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 12:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/29 14:48:36 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	find_index(t_list *a, int value)
{
	int	index;

	index = 0;
	while (a)
	{
		if (a->content == value)
			return (index);
		a = a->next;
		index++;
	}
	return (-1);
}

void	sort_two_or_three(t_list **a)
{
	int	size;

	size = ft_lstsize(*a);
	if (size == 2)
	{
		if ((*a)->content > (*a)->next->content)
			sa(a, 1);
	}
	else if (size == 3)
	{
		if ((*a)->content > (*a)->next->content)
			sa(a, 1);
		if ((*a)->next->content > (*a)->next->next->content)
			rra(a, 1);
		if ((*a)->content > (*a)->next->content)
			sa(a, 1);
	}
}

void	sort_four_or_five(t_list **a, t_list **b)
{
	int	min;

	while (ft_lstsize(*a) > 3)
	{
		min = find_min(*a);
		if (find_index(*a, min) <= ft_lstsize(*a) / 2)
		{
			while ((*a)->content != min)
				ra(a, 1);
		}
		else
		{
			while ((*a)->content != min)
				rra(a, 1);
		}
		pb(a, b, 1);
	}
	sort_two_or_three(a);
	while (*b)
		pa(a, b, 1);
}

void	sort_small_stack(t_list **a, t_list **b)
{
	int	size;

	size = ft_lstsize(*a);
	if (size <= 3)
		sort_two_or_three(a);
	else if (size == 4 || size == 5)
		sort_four_or_five(a, b);
}
