/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:27:18 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/25 15:30:59 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "exec.h"
#include "ms_error.h"

// TODO: Set exit code on malloc fail
// TODO: Change the builtin signature to use the s_exec instead?
t_exec	*init_exec(t_str cmd, t_ast *head, t_token *tkns, t_alist *env_lst)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (exec == NULL)
		return (ms_error(PERROR, NULL, NULL), NULL);
	ft_memcpy(exec->dup_std_fd, (int [2]){-1, -1}, 2 * sizeof(int));
	if (!store_std_fd(exec->dup_std_fd))
	{
		ms_error(PERROR, NULL, NULL);
		free(exec);
		return (NULL);
	}
	exec->redir_fd[0] = STDIN;
	exec->redir_fd[1] = STDOUT;
	exec->wstatus = 0;
	exec->is_child = false;
	exec->cmd = cmd;
	exec->head = head;
	exec->tokens = tkns;
	exec->env_lst = env_lst;
	return (exec);
}

void	free_exec(t_exec **exec)
{
	// apply_std_redirection((*exec)->dup_std_fd);
	if ((*exec)->is_child || !apply_std_redirection((*exec)->dup_std_fd))
		close_redir((*exec)->dup_std_fd);
	close_redir((*exec)->redir_fd);
	free(*exec);
	*exec = NULL;
}
