/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_rules.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 10:27:28 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/12 09:04:12 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **a)
{
	t_list	*first;
	t_list	*second;

	if (a && *a && (*a)->next)
	{
		first = *a;
		second = first->next;
		first->next = second->next;
		second->next = first;
		*a = second;
		write(1, "sa\n", 3);
	}
}

void	sb(t_list **b)
{
	t_list	*first;
	t_list	*second;

	if (b && *b && (*b)->next)
	{
		first = *b;
		second = first->next;
		first->next = second->next;
		second->next = first;
		*b = second;
		write(1, "sb\n", 3);
	}
}

void	ss(t_list **a, t_list **b)
{
	sa(a);
	sb(b);
	write(1, "ss\n", 3);
}
