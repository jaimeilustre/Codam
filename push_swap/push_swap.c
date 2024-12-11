/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/06 08:44:08 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/11 15:13:25 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void push_swap(t_list **a, t_list **b, int total_elements)
{
    int *chunks;
    int chunk_count;
    int i;

    create_chunks(a, b, total_elements, &chunks, &chunk_count);
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

int find_index(t_list *a, int value)
{
    int index = 0;

    while (a)
    {
        if (a->content == value)
            return index;
        a = a->next;
        index++;
    }
    return -1;
}

void sort_small_stack(t_list **a, t_list **b)
{
    int size = ft_lstsize(*a);

    if (size == 2)
    {
        if ((*a)->content > (*a)->next->content)
            sa(a);
        return;
    }
    else if (size == 3)
    {
        while (!is_sorted(*a))
        {
            if ((*a)->content > (*a)->next->content)
                sa(a);
            if (!is_sorted(*a))
                rra(a);
        }
        return;
    }
    else if (size == 4 || size == 5)
    {
        while (ft_lstsize(*a) > 3)
        {
            int min = find_min(*a);
            if (find_index(*a, min) <= ft_lstsize(*a) / 2)
                while ((*a)->content != min)
                    ra(a);
            else
                while ((*a)->content != min)
                    rra(a);
            pb(a, b);
        }
        sort_small_stack(a, NULL);
        while (*b)
            pa(a, b);
	}
}

int	is_sorted(t_list *a)
{
	while (a && a->next)
	{
		if (a->content > a->next->content)
			return (0);
		a = a->next;
	}
	return (1);
}

int main(int argc, char **argv)
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
