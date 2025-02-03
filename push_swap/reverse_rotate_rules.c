/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_rotate_rules.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 16:25:43 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/03 21:21:56 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_list **a, int output_flag)
{
	t_list	*second_last;
	t_list	*last;

	if (a && *a && (*a)->next)
	{
		second_last = NULL;
		last = *a;
		while (last->next)
		{
			second_last = last;
			last = last->next;
		}
		second_last->next = NULL;
		last->next = *a;
		*a = last;
		if (output_flag == 1)
			ft_putendl_fd("rra", STDOUT_FILENO);
	}
}

void	rrb(t_list **b, int output_flag)
{
	t_list	*second_last;
	t_list	*last;

	if (b && *b && (*b)->next)
	{
		second_last = NULL;
		last = *b;
		while (last->next)
		{
			second_last = last;
			last = last->next;
		}
		second_last->next = NULL;
		last->next = *b;
		*b = last;
		if (output_flag == 1)
			ft_putendl_fd("rrb", STDOUT_FILENO);
	}
}

void	rrr(t_list **a, t_list **b, int output_flag)
{
	rra(a, 0);
	rrb(b, 0);
	if (output_flag == 1)
		ft_putendl_fd("rrr", STDOUT_FILENO);
}
