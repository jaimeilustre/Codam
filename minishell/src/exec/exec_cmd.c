/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:23:02 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/25 15:04:03 by jilustre      ########   odam.nl         */
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

static t_str	get_cmd_path(t_str cmd, t_exec *exec)
{
	t_str	path_to_cmd;

	path_to_cmd = find_cmd(cmd, exec->env_lst);
	if (path_to_cmd == NULL && exec->is_child)
		exit_process(exec);
	return (path_to_cmd);
}

// TODO: Parent stop listing to signals and let external program deal with it?
static bool	exec_program(t_ast *node, t_exec *exec)
{
	t_str	path_to_cmd;
	pid_t	cpid;
	t_alist	env;

	path_to_cmd = get_cmd_path(*(node->args), exec);
	if (path_to_cmd == NULL)
		return (true);
	free(*(node->args));
	*(node->args) = path_to_cmd;
	if (!exec->is_child)
	{
		if (!start_fork(&cpid, exec))
			return (false);
		else if (cpid != 0)
			return (wait_or_kill_child(cpid, exec), true);
	}
	if (duplicate_list(&env, exec->env_lst, ENV_EXPORT, ENV_UNLIST))
		execve(path_to_cmd, node->args, env.items);
	ms_error(PERROR, path_to_cmd, NULL);
	free_list(&env);
	exit_process(exec);
	return (false);
}

// TODO: If redirection fails continue but set exit code to 1
bool	exec_cmd(t_ast *node, t_exec *exec)
{
	expand_variables(node, exec);
	// if (!apply_redirection(node, exec))
	if (!apply_redirection(node->redirect, exec->redir_fd))
	{
		exec->wstatus = 1;
		if (exec->is_child)
			exit_process(exec);
		else
			return (false);
	}
	if (exec_builtin(node, exec))
		return (true);
	return (exec_program(node, exec));
}
