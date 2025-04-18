/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:19:15 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/18 14:16:57 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "minishell.h"
#include "exec.h"
#include "ms_error.h"

static t_exit_code	exec_subnode(t_ast *node, t_exec *exec)
{
	t_exit_code	exit_code;

	exit_code = exec_node(node, exec);
	store_exit_code(exec->env_lst, exit_code);
	if (apply_std_redirection(exec->dup_std_fd))
		return (exit_code);
	ms_error(PERROR, NULL, NULL);
	return (E_GEN_ERR);
}

static t_exit_code	exec_logical(t_ast *node, t_exec *exec)
{
	t_exit_code	exit_code;

	exit_code = exec_subnode(node->left, exec);
	if (exit_code != E_TERM
		&& ((node->type == NODE_AND && exit_code == 0)
			|| (node->type == NODE_OR && exit_code != 0)))
		exit_code = exec_subnode(node->right, exec);
	return (exit_code);
}

static t_exit_code	exec_subshell(t_ast *node, t_exec *exec)
{
	pid_t		cpid;
	t_exit_code	exit_code;

	if (!start_fork(&cpid, exec))
		return (E_GEN_ERR);
	else if (cpid == 0)
	{
		if (dup_fd_into(exec->redir_fd, exec->dup_std_fd))
			exit_code = exec_node(node->left, exec);
		else
		{
			ms_error(PERROR, NULL, NULL);
			exit_code = E_GEN_ERR;
		}
		exit_process(exec, exit_code);
	}
	return (wait_on_child(cpid));
}

t_exit_code	exec_node(t_ast *node, t_exec *exec)
{
	if (node == NULL)
		return (E_GEN_ERR);
	else if (node->type == NODE_PIPE)
		return (exec_pipe(node, exec));
	else if (node->type == NODE_AND || node->type == NODE_OR)
		return (exec_logical(node, exec));
	else if (node->type == NODE_COMMAND)
		return (exec_cmd(node, exec));
	else if (node->type == NODE_SUBSHELL)
		return (exec_subshell(node, exec));
	return (E_GEN_ERR);
}
