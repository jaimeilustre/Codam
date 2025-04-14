/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   std_redir.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/14 15:38:32 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/14 15:39:48 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "minishell.h"
#include "exec.h"

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

bool	apply_std_redirection(int pipe_fd[2])
{
	const int	std[2] = {STDIN, STDOUT};
	int			i;

	i = 0;
	while (i < 2)
	{
		if (pipe_fd[i] != std[i] && !redirect_fd(&(pipe_fd[i]), std[i]))
			return (false);
		++i;
	}
	return (true);
}
