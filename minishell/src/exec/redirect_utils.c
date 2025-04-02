/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 14:04:17 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/24 18:06:23 by jboon         ########   odam.nl         */
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
