/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:46:28 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/16 07:38:15 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	parse_arguments_to_int(char *arg, t_list **stack)
{
	long	nb_long;
	int		nb;
	t_list	*new_node;

	if (!check_valid_int(arg))
		exit_error(stack, NULL, NULL);
	nb_long = ft_atoi(arg);
	if (nb_long > INT_MAX || nb_long < INT_MIN)
		exit_error(stack, NULL, NULL);
	nb = (int)nb_long;
	new_node = ft_lstnew(nb);
	if (!new_node)
		exit_error(stack, NULL, NULL);
	ft_lstadd_back(stack, new_node);
}

void	split_and_parse(char *arg, t_list **stack)
{
	char	**split_array;
	int		i;

	split_array = ft_split(arg, ' ');
	if (!split_array || !split_array[0])
	{
		free_split(split_array);
		exit_error(stack, NULL, NULL);
	}
	i = 0;
	while (split_array[i])
	{
		parse_arguments_to_int(split_array[i], stack);
		i++;
	}
	free_split(split_array);
}

t_list	*parse_arguments(int argc, char **argv)
{
	t_list	*stack;
	int		i;

	stack = NULL;
	if (argc == 2)
		split_and_parse(argv[1], &stack);
	else
	{
		i = 1;
		while (i < argc)
		{
			parse_arguments_to_int(argv[i], &stack);
			i++;
		}
	}
	if (check_duplicate_int(stack))
		exit_error(&stack, NULL, NULL);
	return (stack);
}
