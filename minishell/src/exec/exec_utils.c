/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 11:08:34 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/21 15:07:08 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <sys/wait.h>
#include "exec.h"
#include "signal_utils.h"
#include "ms_error.h"
#include "libft.h"

int	get_exit_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (0);
}

void	wait_or_kill_child(pid_t cpid, t_exec *exec)
{
	if (g_signal == 0)
		waitpid(cpid, &exec->wstatus, 0);
	if (g_signal != 0)
	{
		kill(cpid, g_signal);
		waitpid(cpid, &exec->wstatus, 0);
	}
}

void	exit_process(t_exec *exec)
{
	int	exit_code;

	exit_code = get_exit_code(exec->wstatus);
	free(exec->cmd);
	free_ast(exec->head);
	free_token_list(&exec->tokens);
	free_list(exec->env_lst);
	free_exec(&exec);
	rl_clear_history();
	exit(exit_code);
}

// TODO: Have parent or child stop listing to signals after fork?
bool	start_fork(pid_t *cpid, t_exec *exec)
{
	*cpid = fork();
	if (*cpid == -1)
		ms_error(PERROR, NULL, NULL);
	else if (*cpid == 0)
		exec->is_child = true;
	return (*cpid != -1);
}
