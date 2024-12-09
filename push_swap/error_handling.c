/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:54:01 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/09 07:54:17 by jilustre      ########   odam.nl         */
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
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);	
}
