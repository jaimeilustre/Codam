/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:43:20 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:50:55 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "exec.h"
#include "ms_error.h"
#include "ms_signals.h"
#include "parser.h"
#include "utils.h"

static pid_t	exec_child(t_ast *node, t_exec *exec, int pipe_fd[2], int *rdir)
{
	pid_t		cpid;

	start_fork(&cpid, exec);
	if (cpid == 0)
	{
		ign_pipe_signal_handler();
		safe_close_fd(&pipe_fd[0]);
		safe_close_fd(rdir);
		*rdir = pipe_fd[1];
		exit_process(exec, exec_node(node, exec));
	}
	return (cpid);
}

t_exit_code	exec_pipe(t_ast *node, t_exec *exec)
{
	pid_t		cpid[2];
	int			pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (ms_error(PERROR, NULL, NULL), E_GEN_ERR);
	cpid[0] = exec_child(node->left, exec, pipe_fd, &exec->redir_fd[1]);
	safe_close_fd(&pipe_fd[1]);
	if (cpid[0] == -1)
		return (safe_close_fd(&pipe_fd[0]), E_GEN_ERR);
	swapi(pipe_fd, (pipe_fd + 1));
	cpid[1] = exec_child(node->right, exec, pipe_fd, &exec->redir_fd[0]);
	safe_close_fd(&pipe_fd[1]);
	if (cpid[1] == -1)
		return (E_GEN_ERR);
	wait_on_child(cpid[0]);
	return (wait_on_child(cpid[1]));
}
