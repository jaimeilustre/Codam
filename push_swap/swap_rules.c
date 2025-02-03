/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_rules.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 10:27:28 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/03 21:22:58 by jaimeilustr   ########   odam.nl         */
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
			ft_putendl_fd("sa", STDOUT_FILENO);
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
			ft_putendl_fd("sb", STDOUT_FILENO);
	}
}

void	ss(t_list **a, t_list **b, int output_flag)
{
	sa(a, 0);
	sb(b, 0);
	if (output_flag == 1)
		ft_putendl_fd("ss", STDOUT_FILENO);
}
