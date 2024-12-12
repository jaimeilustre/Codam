/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_rotate_rules.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 16:25:43 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/12 09:04:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_list **a)
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
		write(1, "rra\n", 4);
	}
}

void	rrb(t_list **b)
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
		write(1, "rrb\n", 4);
	}
}

void	rrr(t_list **a, t_list **b)
{
	rra(a);
	rrb(b);
	write(1, "rrr\n", 3);
}
