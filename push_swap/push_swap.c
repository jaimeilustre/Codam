/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/06 08:44:08 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/08 14:44:41 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_valid_int(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_duplicate_int(t_list *stack)
{
	t_list	*outer;
	t_list	*inner;

	outer = stack;
	while (outer)
	{
		inner = outer->next;
		while (inner)
		{
			if (outer->content == inner->content)
				return (1);
			inner = inner->next;
		}
		outer = outer->next;
	}
	return (0);
}

int	find_min(t_list *stack)
{
	int	min;
	
	min = INT_MAX;
	while (stack)
	{
		if (stack->content < min)
			min = stack->content;
		stack = stack->next;
	}
	return (min);
}

int	find_max(t_list *stack)
{
	int	max;

	max = INT_MIN;
	while (stack)
	{
		if (stack->content > max)
			max = stack->content;
		stack = stack->next;
	}
	return (max);
}

void	exit_error(t_list **a, t_list **b, int *chunks)
{
	if (a && *a)
		ft_lstclear(a);
	if (b && *b)
		ft_lstclear(b);
	if (chunks)
		free(chunks);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);	
}

void free_split(char **split_array)
{
    int i;

    if (split_array)
    {
        i = 0;
        while (split_array[i])  // Loop through the array of strings
        {
            free(split_array[i]);  // Free each string
            i++;
        }
        free(split_array);  // Finally, free the array itself
    }
}

t_list	*parse_arguments(int argc, char **argv)
{
	t_list	*stack;
	t_list	*new_node;
	int		i;
	int		nb;
	char	**split_array;
	
	stack = NULL;
	i = 1;

	if (argc == 2)
	{
		split_array = ft_split(argv[1], ' ');
		if (!split_array)
			exit_error(&stack, NULL, NULL);
		while (split_array[i - 1])
		{
			if (!check_valid_int(split_array[i - 1]))
				exit_error(&stack, NULL, NULL);
			nb = ft_atoi(split_array[i - 1]);
			new_node = ft_lstnew(nb);
			if (!new_node)
				exit_error(&stack, NULL, NULL);
			ft_lstadd_back(&stack, new_node);
			i++;
		}
		free_split(split_array);
	}
	else
	{
		while (i < argc)
		{
			if (!check_valid_int(argv[i]))
				exit_error(&stack, NULL, NULL);
			nb = ft_atoi(argv[i]);
			new_node = ft_lstnew(nb);
			if (!new_node)
				exit_error(&stack, NULL, NULL);
			ft_lstadd_back(&stack, new_node);
			i++;
		}
	}
	if (check_duplicate_int(stack))
		exit_error(&stack, NULL, NULL);
	return (stack);
}

void	create_chunks(int total_elements, int **chunks, int *chunk_count)
{
	int	chunk_size;
	int	i;

	if (total_elements < 100)
		chunk_size = 5;
	else
		chunk_size = total_elements / 10;
	*chunks = malloc(sizeof(int) * ((total_elements / chunk_size) + 1));
	if (!*chunks)
		exit_error(NULL, NULL, NULL);
	i = 0;
	while (i <= total_elements / chunk_size)
	{
		(*chunks)[i] = i * chunk_size;
		i++;
	}
	*chunk_count = i;
}

int	calculator_rotation_cost(t_list *stack, int target)
{
	int		forward_steps;
	int		reverse_steps;
	int		total_size;
	t_list	*current;
	
	forward_steps = 0;
	current = stack;
	while (current && current->content != target)
	{
		forward_steps++;
		current = current->next;
	}
	total_size = ft_lstsize(stack);
	reverse_steps = total_size - forward_steps;
	if (forward_steps <= reverse_steps)
		return (forward_steps);
	else
		return (-reverse_steps);
}

void	push_min_cost_element(t_list **a, t_list **b, int chunk_min, int chunk_max)
{
	t_list	*current;
	int		min_cost;
	int		best_target;
	int		cost;

	current = *a;
	min_cost = INT_MAX;
	best_target = 0;
	while (current)
	{
		if (current->content >= chunk_min && current->content <= chunk_max)
		{
			cost = calculator_rotation_cost(*a, current->content);
			if (abs(cost) < abs(min_cost))
			{
				min_cost = cost;
				best_target = current->content;
			}	
		}
		current = current->next;
	}
	while ((*a)->content != best_target)
	{
		if (min_cost > 0)
			ra(a);
		else
			rra(a);
	}
	pb(a, b);
}

void	push_to_b(t_list **a, t_list **b, int chunk_min, int chunk_max)
{
	t_list	*current;
	int		has_target;
	
	while (*a)
	{
		current = *a;
		has_target = 0;
		while (current)
		{
			if (current->content >= chunk_min && current->content <= chunk_max)
			{
				has_target = 1;
				break ;
			}
			current = current->next;
		}
		if (!has_target)
			break ;
		push_min_cost_element(a, b, chunk_min, chunk_max);
		if (*b && (*b)->next && (*b)->content < (*b)->next->content)
			sb(b);
	}
}

void	sort_b_to_a(t_list **a, t_list **b)
{
	int	max;
	int	rotation;
	
	while (*b)
	{
		max = find_max(*b);
		rotation = calculator_rotation_cost(*b, max);
		while ((*b)->content != max)
		{
			if (rotation > 0)
				rb(b);
			else
				rrb(b);
		}
		pa(a, b);
	}
}

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

void	sort_small_stack(t_list **a)
{
	if (ft_lstsize(*a) == 2)
    {
        if ((*a)->content > (*a)->next->content)
            sa(a); // Swap if out of order
    }
    else if (ft_lstsize(*a) == 3)
    {
        int first = (*a)->content;
        int second = (*a)->next->content;
        int third = (*a)->next->next->content;

        if (first > second && first > third)
            ra(a); // Rotate if the first element is the largest
        else if ((*a)->content > (*a)->next->content)
            sa(a); // Swap the top two elements if out of order
        else if ((*a)->next->content > (*a)->next->next->content)
            rra(a); // Reverse rotate to position the smallest element last
    }
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
		sort_small_stack(&a);
	else
		push_swap(&a, &b, ft_lstsize(a));
	ft_lstclear(&a);
	ft_lstclear(&b);
	return (0);
}
