/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_rules.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 10:27:28 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/20 12:25:44 by jilustre      ########   odam.nl         */
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
	}
}

void	ss(t_list **a, t_list **b)
{
	sa(a);
	sb(b);
}

// int main(void)
// {
//     t_list *stack = ft_lstnew(1);
//     stack->next = ft_lstnew(2);
//     stack->next->next = ft_lstnew(3);

// 	printf("Original stack:\n");
// 	print_list(stack);
// 	sa(&stack);
// 	printf("Modified stack:\n");
// 	print_list(stack);
// 	free_list(stack);
// 	return (0);	
// }
