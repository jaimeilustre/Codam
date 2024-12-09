/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/06 08:44:08 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/09 16:33:00 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_list **a, t_list **b, int total_elements)
{
	int	*chunks;
	int	chunk_count;
	int	i;
	
	chunks = NULL;
	create_chunks(total_elements, &chunks, &chunk_count);
	i = 0;
	while (i < chunk_count)
	{
		push_to_b(a, b, chunks[i], (i == chunk_count - 1) ? INT_MAX : chunks[i + 1] - 1);
		i++;
	}
	sort_b_to_a(a, b);
	free(chunks);
}

void	sort_small_stack(t_list **a, t_list **b)
{
	int min;

    min = find_min(*a);
    while (ft_lstsize(*a) > 3)
    {
        if ((*a)->content == min)
        {
            pb(a, b);
            min = find_min(*a);
        }
        else
            ra(a);
    }
    if ((*a)->content > (*a)->next->content && (*a)->content > (*a)->next->next->content)
        ra(a);
    if ((*a)->content > (*a)->next->content)
        sa(a);
    if ((*a)->next->content > (*a)->next->next->content)
    {
        rra(a);
        if ((*a)->content > (*a)->next->content)
            sa(a);
    }
    while (*b)
        pa(a, b);

}

int main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	
	if (argc < 2)
		return (0);
	a = parse_arguments(argc, argv);
	b = NULL;
	
	if (ft_lstsize(a) <= 3)
		sort_small_stack(&a, &b);
	else
		push_swap(&a, &b, ft_lstsize(a));
	ft_lstclear(&a);
	ft_lstclear(&b);
	return (0);
}
