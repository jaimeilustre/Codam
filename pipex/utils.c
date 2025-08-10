/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/17 07:25:44 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/17 07:41:55 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "pipex.h"

void	handle_error(const char *cmd, const char *msg)
{
	char	*error_message;

	error_message = strerror(errno);
	write(STDERR_FILENO, "bash: ", 7);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	write(STDERR_FILENO, "\n", 1);
}

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
