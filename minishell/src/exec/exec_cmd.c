/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:23:02 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:59:50 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "libft.h"

#include "builtin.h"
#include "exec.h"
#include "list.h"
#include "ms_error.h"
#include "ms_signals.h"
#include "ms_string.h"
#include "parser.h"

static t_exit_code	set_cmd_path(t_str *cmd_path, t_str *cmd, t_exec *exec)
{
	struct stat	statbuf;

	if (is_rel_abs_path(*cmd))
	{
		if (stat(*cmd, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				return (ms_error(IS_DIR, *cmd, NULL), E_CMD_NO_PERM);
			*cmd_path = *cmd;
			return (E_SUCCESS);
		}
		return (ms_error(PERROR, *cmd, NULL), E_CMD_NOT_FOUND);
	}
	*cmd_path = find_cmd(*cmd, exec->env_lst);
	if (*cmd_path != NULL)
	{
		free(*cmd);
		*cmd = *cmd_path;
		return (E_SUCCESS);
	}
	return (E_CMD_NOT_FOUND);
}

static t_exit_code	exec_builtin(t_ast *node, t_exec *exec)
{
	t_blt_func	blt_func;
	t_exit_code	exit_code;

	blt_func = find_builtin(*(node->args));
	if (blt_func == NULL)
		return (E_NO_BLTIN);
	if (blt_func == ms_exit)
		exit_code = blt_func(count_args(node->args), node->args, exec);
	else
		exit_code = blt_func(count_args(node->args), node->args, exec->env_lst);
	return (exit_code);
}

static t_exit_code	ms_execve(t_str cmd, t_str *argv, t_exec *exec)
{
	t_alist		env;
	t_exit_code	exit_code;

	errno = 0;
	dfl_signal_handler();
	if (duplicate_list(&env, exec->env_lst, ENV_EXPORT, ENV_UNLIST))
		execve(cmd, argv, env.items);
	ms_error(PERROR, cmd, NULL);
	shallow_free_list(&env);
	if (errno == EACCES)
		exit_code = E_CMD_NO_PERM;
	else if (errno == ENOENT)
		exit_code = E_CMD_NOT_FOUND;
	else
		exit_code = E_GEN_ERR;
	exit_process(exec, exit_code);
	return (exit_code);
}

static t_exit_code	exec_program(t_ast *node, t_exec *exec)
{
	t_str		path_to_cmd;
	pid_t		cpid;
	t_exit_code	exit_code;

	path_to_cmd = NULL;
	exit_code = set_cmd_path(&path_to_cmd, node->args, exec);
	if (exit_code != E_SUCCESS)
		return (exit_code);
	if (!start_fork(&cpid, exec))
		return (E_GEN_ERR);
	else if (cpid != 0)
		return (wait_on_child(cpid));
	return (ms_execve(path_to_cmd, node->args, exec));
}

t_exit_code	exec_cmd(t_ast *node, t_exec *exec)
{
	t_exit_code	exit_code;
	t_alist		ls;

	ft_bzero(&ls, sizeof(t_alist));
	if (!expand_argv(node->args, exec->env_lst, &ls)
		|| !apply_redirection(node->redirect, exec->redir_fd, exec->env_lst))
	{
		free_list(&ls);
		return (E_GEN_ERR);
	}
	free(ls.flags);
	free_args(node->args);
	node->args = ls.items;
	if (*node->args == NULL)
		return (E_SUCCESS);
	exit_code = exec_builtin(node, exec);
	if (exit_code != E_NO_BLTIN)
		return (exit_code);
	return (exec_program(node, exec));
}
