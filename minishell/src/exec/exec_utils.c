/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 11:08:34 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/18 14:22:50 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"
#include "ms_signals.h"
#include "ms_error.h"
#include "exec.h"

t_exit_code	get_exit_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (E_INV_ARG + WTERMSIG(wstatus));
	return (E_SUCCESS);
}

void	store_exit_code(t_alist *env_lst, t_exit_code exit_code)
{
	t_str	str_code;
	t_str	entry;

	str_code = ft_itoa(exit_code);
	if (str_code == NULL)
		return ;
	entry = ft_strjoin(V_EXIT"=", str_code);
	if (entry != NULL)
		ms_decl_setenv(env_lst, V_EXIT, entry, ENV_HIDDEN);
	free(entry);
	free(str_code);
}

t_exit_code	wait_on_child(pid_t cpid)
{
	int	wstatus;

	while (waitpid(cpid, &wstatus, 0) != cpid)
		;
	//TODO: SIGINT and SIGQUIT should display newline
	return (get_exit_code(wstatus));
}

void	exit_process(t_exec *exec, t_exit_code exit_code)
{
	free(exec->cmd);
	free_ast(exec->head);
	free_token_list(&exec->tokens);
	free_list(exec->env_lst);
	free_exec(&exec);
	rl_clear_history();
	exit(exit_code);
}

bool	start_fork(pid_t *cpid, t_exec *exec)
{
	*cpid = fork();
	if (*cpid == -1)
		ms_error(PERROR, NULL, NULL);
	else if (*cpid == 0)
		exec->is_child = true;
	return (*cpid != -1);
}
