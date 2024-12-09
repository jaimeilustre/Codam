/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:46:28 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/09 08:57:12 by jilustre      ########   odam.nl         */
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

void free_split(char **split_array)
{
    int i;

    if (split_array)
    {
        i = 0;
        while (split_array[i])
		{
            free(split_array[i]);
            i++;
        }
        free(split_array);
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
		if (!split_array || !split_array[0])
			exit_error(&stack, NULL, NULL);
		while (split_array[i - 1])
		{
			if (!check_valid_int(split_array[i - 1]))
				exit_error(&stack, NULL, NULL);
			nb = ft_atoi(split_array[i - 1]);
			if (nb == INT_MAX || nb == INT_MIN)
				exit_error(&stack, NULL, NULL);
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
			if (nb == INT_MAX || nb == INT_MIN)
				exit_error(&stack, NULL, NULL);
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

