/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 14:04:17 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/14 15:39:52 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"
#include "exec.h"

static bool	is_std(int fd)
{
	return (fd == STDIN || fd == STDOUT || fd == STDERR);
}

void	safe_close_fd(int *fd)
{
	if (*fd == -1 || (isatty(*fd) && is_std(*fd)))
		return ;
	close (*fd);
	*fd = -1;
}

bool	redirect_fd(int *fd, int dupfd)
{
	if (*fd == -1 || dupfd == -1 || (!is_std(*fd) && dup2(*fd, dupfd) == -1))
	{
		safe_close_fd(fd);
		return (false);
	}
	safe_close_fd(fd);
	*fd = dupfd;
	return (true);
}

void	close_redir(int fd[2])
{
	safe_close_fd(&fd[0]);
	safe_close_fd(&fd[1]);
}
