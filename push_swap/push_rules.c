/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_rules.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 12:13:18 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/20 14:21:08 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_list **a, t_list **b)
{
	t_list	*temp;
	
	if (*b)
	{
		temp = *b;
		*b = (*b)->next;
		ft_lstadd_front(a, temp);
	}
}

void	pb(t_list **a, t_list **b)
{
	t_list	*temp;
	
	if (*b)
	{
		temp = *a;
		*a = (*a)->next;
		ft_lstadd_front(b, temp);
	}
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

// 	printf("\nTesting pa:\n");
// 	pa(&a, &b);
// 	print_list(a);
// 	print_list(b);
	
// 	printf("\nTesting pb:\n");
// 	pb(&a, &b);
// 	print_list(a);
// 	print_list(b);
	
// 	free_list(a);
// 	free_list(b);
	
// 	return (0);	
// }
