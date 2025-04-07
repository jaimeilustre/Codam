/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:43:20 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/04 16:11:55 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include "ms_error.h"

static pid_t	exec_child(t_ast *node, t_exec *exec, int pipe_fd[2], int *rdir)
{
	pid_t	cpid;

	start_fork(&cpid, exec);
	if (cpid == 0)
	{
		safe_close_fd(&pipe_fd[0]);
		safe_close_fd(rdir);
		*rdir = pipe_fd[1];
		exec_node(node, exec);
		exit_process(exec);
	}
	return (cpid);
}

bool	exec_pipe(t_ast *node, t_exec *exec)
{
	pid_t	cpid[2];
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (ms_error(PERROR, NULL, NULL), false);
	cpid[0] = exec_child(node->left, exec, pipe_fd, &exec->redir_fd[1]);
	safe_close_fd(&pipe_fd[1]);
	if (cpid[0] == -1)
		return (safe_close_fd(&pipe_fd[0]), false);
	swapi(pipe_fd, (pipe_fd + 1));
	cpid[1] = exec_child(node->right, exec, pipe_fd, &exec->redir_fd[0]);
	safe_close_fd(&pipe_fd[1]);
	if (cpid[1] == -1)
		return (false);
	wait_or_kill_child(cpid[0], exec);
	wait_or_kill_child(cpid[1], exec);
	if (exec->is_child)
		exit_process(exec);
	return (true);
}
