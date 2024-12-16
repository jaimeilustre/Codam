/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/06 08:44:08 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/16 15:28:19 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_list **a, t_list **b, int total_elements)
{
	int				*chunks;
	int				chunk_count;
	int				i;
	t_chunk_data	data;

	data.a = a;
	data.b = b;
	data.chunks = &chunks;
	data.chunk_count = &chunk_count;
	data.total_elements = total_elements;
	create_chunks(&data);
	i = 0;
	while (i < chunk_count)
	{
		if (i == 0)
			push_to_b(a, b, INT_MIN, chunks[i]);
		else
			push_to_b(a, b, chunks[i - 1] + 1, chunks[i]);
		i++;
	}
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
