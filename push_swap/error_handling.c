/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:54:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/04 05:45:31 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_error(t_list **a, t_list **b, int *chunks)
{
	if (a && *a)
		ft_lstclear(a);
	if (b && *b)
		ft_lstclear(b);
	if (chunks)
		free(chunks);
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
