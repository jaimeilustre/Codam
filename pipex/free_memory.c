/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:18:37 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/16 15:18:49 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
