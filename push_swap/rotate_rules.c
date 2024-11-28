/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_rules.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 14:29:25 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/20 16:45:03 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_list **a)
{
	t_list	*temp;

	if (a && *a && (*a)->next)
	{
		temp = *a;
		*a = (*a)->next;
		temp->next = NULL;
		ft_lstadd_back(a, temp);
	}
}

void	rb(t_list **b)
{
	t_list	*temp;

	if (b && *b && (*b)->next)
	{
		temp = *b;
		*b = (*b)->next;
		temp->next = NULL;
		ft_lstadd_back(b, temp);
	}
}

void	rr(t_list **a, t_list **b)
{
	ra(a);
	rb(b);
}

// int main(void)
// {
//     t_list *a = ft_lstnew(1);
//     a->next = ft_lstnew(2);
//     a->next->next = ft_lstnew(3);

// 	t_list *b = ft_lstnew(4);
//     b->next = ft_lstnew(5);
//     b->next->next = ft_lstnew(6);

// 	printf("Original stacks:\n");
// 	print_list(a);
// 	print_list(b);

// 	printf("\nTesting ra:\n");
// 	ra(&a);
// 	print_list(a);
	
// 	printf("\nTesting rb:\n");
// 	rb(&b);
// 	print_list(b);
	
// 	free_list(a);
// 	free_list(b);
	
// 	return (0);	
// }
