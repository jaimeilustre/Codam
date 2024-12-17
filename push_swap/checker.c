/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/16 12:00:05 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/17 08:15:21 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "get_next_line.h"

void	read_instructions(t_list **a, t_list **b, char *instruction)
{
	if (ft_strncmp(instruction, "sa", 2) == 0 && instruction[2] == '\n')
		sa(a, 0);
	else if (ft_strncmp(instruction, "sb", 2) == 0 && instruction[2] == '\n')
		sb(b, 0);
	else if (ft_strncmp(instruction, "ss", 2) == 0 && instruction[2] == '\n')
		ss(a, b, 0);
	else if (ft_strncmp(instruction, "pa", 2) == 0 && instruction[2] == '\n')
		pa(a, b, 0);
	else if (ft_strncmp(instruction, "pb", 2) == 0 && instruction[2] == '\n')
		pb(a, b, 0);
	else if (ft_strncmp(instruction, "ra", 2) == 0 && instruction[2] == '\n')
		ra(a, 0);
	else if (ft_strncmp(instruction, "rb", 2) == 0 && instruction[2] == '\n')
		rb(b, 0);
	else if (ft_strncmp(instruction, "rr", 2) == 0 && instruction[2] == '\n')
		rr(a, b, 0);
	else if (ft_strncmp(instruction, "rra", 3) == 0 && instruction[3] == '\n')
		rra(a, 0);
	else if (ft_strncmp(instruction, "rrb", 3) == 0 && instruction[3] == '\n')
		rrb(b, 0);
	else if (ft_strncmp(instruction, "rrr", 3) == 0 && instruction[3] == '\n')
		rrr(a, b, 0);
	else
		exit_error(NULL, NULL, NULL);
}

void	checker(t_list **a, t_list **b)
{
	char	*instruction;

	while (1)
	{
		instruction = get_next_line(STDIN_FILENO);
		if (!instruction)
			break ;
		read_instructions(a, b, instruction);
		free(instruction);
	}
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
	checker(&a, &b);
	if (is_sorted(a))
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
	ft_lstclear(&a);
	ft_lstclear(&b);
	return (0);
}
