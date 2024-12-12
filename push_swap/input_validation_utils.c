/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_validation_utils.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 13:41:16 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/12 13:42:40 by jilustre      ########   odam.nl         */
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

void	free_split(char **split_array)
{
	int	i;

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
