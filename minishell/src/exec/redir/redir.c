/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 11:46:10 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/28 11:39:42 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"

#include "exec.h"
#include "list.h"
#include "minishell.h"
#include "ms_error.h"
#include "ms_string.h"
#include "parser.h"

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

static bool	redir(t_cstr file, int flags, int perms, int std_fd)
{
	int	fd;

	fd = open(file, flags, perms);
	return (fd != 1 && redirect_fd(&fd, std_fd));
}

static bool	handle_redir(t_cstr file, t_node_type type, int dir_fd[2])
{
	const int	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int	wr_flags = O_CREAT | O_WRONLY;

	if (type == NODE_REDIRECT_IN)
		return (redir(file, O_RDONLY, perms, dir_fd[0]));
	else if (type == NODE_REDIRECT_OUT)
		return (redir(file, wr_flags | O_TRUNC, perms, dir_fd[1]));
	else if (type == NODE_APPEND)
		return (redir(file, wr_flags | O_APPEND, perms, dir_fd[1]));
	return (false);
}

/* Expand file to its string literal and store it in outfile */
static int	file_expansion(t_cstr file, t_alist *env_lst, t_str *outfile)
{
	t_exp	exp;

	ft_bzero(&exp, sizeof(exp));
	exp.sb_off = -1;
	if (!init_list(&exp.ls, 10) || expand_arg(file, &exp, env_lst) == -1)
		return (free_exp(&exp), -1);
	if (exp.ls.size > 1 || (exp.ls.size == 0 && exp.sb.str == NULL))
	{
		free_exp(&exp);
		*outfile = NULL;
	}
	else if (exp.ls.size == 1)
	{
		*outfile = exp.ls.items[0];
		free_strb(&exp.sb);
	}
	else
		*outfile = exp.sb.str;
	shallow_free_list(&exp.ls);
	return (*outfile != NULL);
}

bool	file_redirection(t_redirect *redir, int dir_fd[2], t_alist *ev_ls)
{
	t_str	file;

	while (redir)
	{
		if (redir->type != NODE_HEREDOC)
		{
			file = NULL;
			if (file_expansion(redir->file, ev_ls, &file) == -1)
				return (ms_error(PERROR, NULL, NULL), false);
			else if (file == NULL)
				return (ms_error(AMB_REDIR, redir->file, NULL), false);
			if (!handle_redir(file, redir->type, dir_fd))
				return (ms_error(PERROR, file, NULL), free(file), false);
			free(file);
		}
		else if (!redir_heredoc(redir->file, dir_fd[0]))
			return (ms_error(PERROR, "heredoc", "(max 65536 bytes)"), false);
		redir = redir->next;
	}
	return (true);
}
