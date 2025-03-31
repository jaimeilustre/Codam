/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 11:46:10 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/25 15:38:14 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft.h" // TODO DELETE?
#include "minishell.h"

#include "exec.h"
#include "ms_error.h"

// void	safe_close_fd(int *fd)
// {
// 	if (*fd == -1 || *fd == STDIN || *fd == STDOUT || *fd == STDERR)
// 		return ;
// 	close (*fd);
// 	*fd = -1;
// }

static bool	redir_in(t_cstr file, int std_fd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd != -1 && redirect_fd(&fd, std_fd));
}

// bool	redirect_fd(int *fd, int dupfd)
// {
// 	if (*fd == -1 || dupfd == -1 || dup2(*fd, dupfd) == -1)
// 		return (safe_close_fd(fd), false);
// 	safe_close_fd(fd);
// 	return (true);
// }

static bool	redir_out(t_cstr file, int std_fd)
{
	const int	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int			fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, perms);
	return (fd != 1 && redirect_fd(&fd, std_fd));
}

// void	close_redir(int fd[2])
// {
// 	safe_close_fd(&fd[0]);
// 	safe_close_fd(&fd[1]);
// }

static bool	redir_append(t_cstr file, int std_fd)
{
	const int	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int			fd;

	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, perms);
	return (fd != 1 && redirect_fd(&fd, std_fd));
}

// TODO: If it fails will we have open fd issues?
bool	apply_std_redirection(int pipe_fd[2])
{
	// static const int	std[2] = {STDIN, STDOUT};
	// int					i;
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

// TODO: file redirection needed
// bool	apply_redirection(t_ast *node, t_exec *exec)
bool	apply_redirection(t_redirect *redir, int redir_fd[2])
{
	// (void)node;
	// if (!apply_std_redirection(exec->redir_fd))
	// 	return (exec->wstatus = 1, false);
	// return (true);
	bool	success;
	t_str	file;

	file = NULL;
	success = apply_std_redirection(redir_fd);
	while (redir && success)
	{
		file = redir->file;
		if (redir->type == NODE_REDIRECT_IN)
			success = redir_in(file, redir_fd[0]);
		else if (redir->type == NODE_REDIRECT_OUT)
			success = redir_out(file, redir_fd[1]);
		else if (redir->type == NODE_APPEND)
			success = redir_append(file, redir_fd[1]);
		redir = redir->next;
	}
	if (success == false)
		ms_error(PERROR, file, NULL);
	return (success);
}
