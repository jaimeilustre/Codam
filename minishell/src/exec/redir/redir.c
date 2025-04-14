/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 11:46:10 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/14 15:39:54 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft.h"
#include "minishell.h"
#include "exec.h"
#include "ms_error.h"

static bool	redir_in(t_cstr file, int std_fd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd != -1 && redirect_fd(&fd, std_fd));
}

static bool	redir_out(t_cstr file, int std_fd)
{
	const int	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int			fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, perms);
	return (fd != 1 && redirect_fd(&fd, std_fd));
}

static bool	redir_append(t_cstr file, int std_fd)
{
	const int	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int			fd;

	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, perms);
	return (fd != 1 && redirect_fd(&fd, std_fd));
}

static bool	redir_heredoc(t_str file, int std_fd)
{
	int	pipe_fd[2];

	if (ft_strlen(file) >= (PIPE_BUF * 16))
		return (errno = EFBIG, false);
	if (pipe(pipe_fd) == -1)
		return (false);
	ft_putstr_fd(file, pipe_fd[1]);
	safe_close_fd(&pipe_fd[1]);
	return (redirect_fd(&pipe_fd[0], std_fd));
}

bool	apply_redirection(t_redirect *redir, int redir_fd[2])
{
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
		else if (redir->type == NODE_HEREDOC)
			success = redir_heredoc(file, redir_fd[0]);
		if (success)
			redir = redir->next;
	}
	if (success == false && redir->type == NODE_HEREDOC)
		ms_error(PERROR, "heredoc", "(max 65536 bytes)");
	else if (success == false)
		ms_error(PERROR, file, NULL);
	return (success);
}
