/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   std_redir.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/14 15:38:32 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/28 11:34:56 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "exec.h"
#include "minishell.h"
#include "ms_error.h"

bool	store_std_fd(int new_fd[RE_MAX_FD])
{
	const int	std[RE_MAX_FD] = {STDIN, STDOUT};
	int			i;
	int			fd;

	i = 0;
	while (i < RE_MAX_FD)
	{
		fd = dup(std[i]);
		if (fd == -1)
		{
			close_redir(new_fd);
			return (false);
		}
		new_fd[i] = fd;
		++i;
	}
	return (true);
}

/* Close new_fd and dup old_fd into it */
bool	dup_fd_into(int old_fd[2], int new_fd[2])
{
	close_redir(new_fd);
	new_fd[0] = dup(old_fd[0]);
	new_fd[1] = dup(old_fd[1]);
	if (new_fd[0] == -1 || new_fd[1] == -1)
		close_redir(new_fd);
	return (new_fd[0] != -1 && new_fd[1] != -1);
}

bool	apply_std_redirection(int pipe_fd[2])
{
	const int	std[2] = {STDIN, STDOUT};
	int			i;

	i = 0;
	while (i < 2)
	{
		if (pipe_fd[i] != std[i] && !redirect_fd(&(pipe_fd[i]), std[i]))
			return (ms_error(PERROR, NULL, NULL), false);
		++i;
	}
	return (true);
}
