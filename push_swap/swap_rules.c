/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_rules.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 10:27:28 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/16 16:28:30 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **a, int output_flag)
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
		if (output_flag == 1)
			write(STDOUT_FILENO, "sa\n", 3);
	}
}

void	sb(t_list **b, int output_flag)
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
		if (output_flag == 1)
			write(STDOUT_FILENO, "sb\n", 3);
	}
}

void	ss(t_list **a, t_list **b, int output_flag)
{
	sa(a, 0);
	sb(b, 0);
	if (output_flag == 1)
		write(STDOUT_FILENO, "ss\n", 3);
}
