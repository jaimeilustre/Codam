/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 11:46:10 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/18 13:50:30 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft.h" // TODO DELETE?
#include "minishell.h"

#include "exec.h"

void	safe_close_fd(int *fd)
{
	if (*fd == -1 || *fd == STDIN || *fd == STDOUT || *fd == STDERR)
		return ;
	close (*fd);
	*fd = -1;
}

bool	redirect_fd(int *fd, int dupfd)
{
	if (*fd == -1 || dupfd == -1 || dup2(*fd, dupfd) == -1)
		return (safe_close_fd(fd), false);
	safe_close_fd(fd);
	return (true);
}

void	close_redir(int fd[2])
{
	safe_close_fd(&fd[0]);
	safe_close_fd(&fd[1]);
}

// TODO: If it fails will we have open fd issues?
bool	apply_std_redirection(int pipe_fd[2])
{
	static const int	std[2] = {STDIN, STDOUT};
	int					i;

	i = 0;
	while (i < 2)
	{
		if (pipe_fd[i] != std[i] && !redirect_fd(&(pipe_fd[i]), std[i]))
			return (false);
		++i;
	}
	return (true);
}

// TODO: file redirection needed
bool	apply_redirection(t_ast *node, t_exec *exec)
{
	(void)node;
	if (!apply_std_redirection(exec->redir_fd))
		return (exec->wstatus = 1, false);
	return (true);
}
