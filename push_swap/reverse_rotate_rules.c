/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_rotate_rules.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 16:25:43 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/20 16:45:25 by jilustre      ########   odam.nl         */
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
	}
}

void	rrr(t_list **a, t_list **b)
{
	rra(a);
	rrb(b);
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
// 	rra(&a);
// 	print_list(a);
	
// 	printf("\nTesting rb:\n");
// 	rrb(&b);
// 	print_list(b);
	
// 	free_list(a);
// 	free_list(b);
	
// 	return (0);	
// }
