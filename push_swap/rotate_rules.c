/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_rules.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 14:29:25 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/16 16:27:49 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_list **a, int output_flag)
{
	t_list	*temp;

	if (a && *a && (*a)->next)
	{
		temp = *a;
		*a = (*a)->next;
		temp->next = NULL;
		ft_lstadd_back(a, temp);
		if (output_flag == 1)
			write(STDOUT_FILENO, "ra\n", 3);
	}
}

void	rb(t_list **b, int output_flag)
{
	t_list	*temp;

	if (b && *b && (*b)->next)
	{
		temp = *b;
		*b = (*b)->next;
		temp->next = NULL;
		ft_lstadd_back(b, temp);
		if (output_flag == 1)
			write(STDOUT_FILENO, "rb\n", 3);
	}
}

void	rr(t_list **a, t_list **b, int output_flag)
{
	ra(a, 0);
	rb(b, 0);
	if (output_flag == 1)
		write(STDOUT_FILENO, "rr\n", 3);
}
