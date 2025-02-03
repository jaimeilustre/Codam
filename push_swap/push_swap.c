/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/06 08:44:08 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/03 21:07:14 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_list *stack)
{
	while (stack && stack->next)
	{
		if (stack->content > stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	push_swap(t_list **a, t_list **b, int total_elements)
{
	int				*chunks;
	int				chunk_count;
	t_chunk_data	data;

	data.a = a;
	data.b = b;
	data.chunks = &chunks;
	data.chunk_count = &chunk_count;
	data.total_elements = total_elements;
	create_chunks(&data);
	sort_b_to_a(a, b);
	free(chunks);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	if (argc < 2)
		return (0);
	a = parse_arguments(argc, argv);
	if (!a)
		return (0);
	b = NULL;
	if (is_sorted(a))
	{
		ft_lstclear(&a);
		return (0);
	}
	if (ft_lstsize(a) <= 5)
		sort_small_stack(&a, &b);
	else
		push_swap(&a, &b, ft_lstsize(a));
	ft_lstclear(&a);
	ft_lstclear(&b);
	return (0);
}
