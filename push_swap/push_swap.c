/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/06 08:44:08 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/06 16:27:03 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Argument validation

int	check_valid_int(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
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

// Argument parsing

t_list	*parse_arguments(int argc, char **argv)
{
	t_list	*stack;
	t_list	*new_node;
	int		i;
	int		nb;

	stack = NULL;
	i = 1;
	while (i < argc)
	{
		if (!check_valid_int(argv[i]))
		{
			write(2, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		nb = ft_atoi(argv[i]);
		new_node = ft_lstnew(nb);
		if (!new_node)
		{
			write(2, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&stack, new_node);
		i++;
	}
	if (check_duplicate_int(stack))
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	return (stack);
}

// Chunk-based sorting algorithm

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

int	find_rotation(t_list *stack, int target)
{
	int		forward_steps;
	int		reverse_steps;
	t_list	*current;

	forward_steps = 0;
	reverse_steps = 0;
	current = stack;
	while (current && current->content != target)
	{
		forward_steps++;
		current = current->next;
	}
	current = stack;
	while (current)
	{
		reverse_steps++;
		current = current->next;
	}
	reverse_steps -= forward_steps;
	if (forward_steps <= reverse_steps)
		return (forward_steps);
	else
		return (-reverse_steps);
}

void	push_to_b(t_list **a, t_list **b, int chunk_min, int chunk_max)
{
	t_list	*current;
	int		has_target;

	while (*a)
	{
		has_target = 0;
		current = *a;
		while (current)
		{
			if (current->content >= chunk_min && current->content <= chunk_max)
			{
				has_target = 1;
				break;
			}
			current = current->next;
		}
		if (!has_target)
			break ;
		
		if ((*a)->content >= chunk_min && (*a)->content <= chunk_max)
			pb(a, b);
		else
			ra(a);
	}
}
void	sort_b_to_a(t_list **a, t_list **b)
{
	int	max;
	int	rotation;
	
	while (*b)
	{
		max = find_max(*b);
		rotation = find_rotation(*b, max);
		if (rotation > 0)
		{
			while (rotation--)
				rb(b);
		}
		else
		{
			while(rotation++)
				rrb(b);
		}
		pa(a, b);
	}
}

void	push_swap(t_list **a, t_list **b, int total_elements)
{
	int	chunk_size;
	int	current_min;
	int	current_max;
	int	chunk_max;
	
	if (total_elements < 10)
		chunk_size = 1;
	else
		chunk_size = total_elements / 10;
	current_min = find_min(*a);
	current_max = find_max(*a);
	while (current_min <= current_max)
	{
		chunk_max = current_min + chunk_size - 1;
		push_to_b(a, b, current_min, chunk_max);
		current_min = chunk_max + 1;
		if (!(*a))
			break ;
	}
	sort_b_to_a(a, b);
}

int main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	
	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	a = parse_arguments(argc, argv);
	push_swap(&a, &b, argc - 1);
	ft_lstclear(&a);
	ft_lstclear(&b);
	return (0);
}
