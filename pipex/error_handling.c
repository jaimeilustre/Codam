/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:09:51 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/16 15:14:30 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
