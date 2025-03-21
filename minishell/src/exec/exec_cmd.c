/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:23:02 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/14 17:24:10 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "builtin.h"
#include "parser.h"
#include "exec.h"

static bool	exec_builtin(t_ast *node, t_exec *exec)
{
	t_blt_func	blt_func;

	blt_func = find_builtin(*(node->args));
	if (blt_func == NULL)
		return (false);
	exec->wstatus = blt_func(count_args(node->args), node->args, exec->env_lst);
	if (exec->is_child)
		exit_process(exec);
	return (true);
}

static bool	exec_program(t_ast *node, t_exec *exec)
{
	t_str		path_to_cmd;
	pid_t		cpid;

	path_to_cmd = find_cmd(*(node->args), exec->env_lst);
	if (path_to_cmd == NULL)
	{
		if (exec->is_child)
			exit_process(exec);
		return (true);
	}
	free(*(node->args));
	*(node->args) = path_to_cmd;
	if (!exec->is_child)
	{
		if (!start_fork(&cpid, exec))
			return (false);
		else if (cpid != 0)
			return (wait_or_kill_child(cpid, exec), true);
	}
	execve(path_to_cmd, node->args, exec->env_lst->items);
	ms_error(PERROR, path_to_cmd, NULL);
	exit_process(exec);
	return (false);
}

// TODO: If redirection fails continue but set exit code to 1
bool	exec_cmd(t_ast *node, t_exec *exec)
{
	expand_variables(node, exec);
	if (!apply_redirection(node, exec))
	{
		if (exec->is_child)
			exit_process(exec);
		else
			return (false);
	}
	if (exec_builtin(node, exec))
		return (true);
	return (exec_program(node, exec));
}
