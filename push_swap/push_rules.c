/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_rules.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 12:13:18 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/03 21:21:32 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_list **a, t_list **b, int output_flag)
{
	t_list	*temp;

	if (*b)
	{
		temp = *b;
		*b = (*b)->next;
		ft_lstadd_front(a, temp);
		if (output_flag == 1)
			ft_putendl_fd("pa", STDOUT_FILENO);
	}
}

void	pb(t_list **a, t_list **b, int output_flag)
{
	t_list	*temp;

	if (*a)
	{
		temp = *a;
		*a = (*a)->next;
		ft_lstadd_front(b, temp);
		if (output_flag == 1)
			ft_putendl_fd("pb", STDOUT_FILENO);
	}
}
