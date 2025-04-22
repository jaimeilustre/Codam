/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:27:18 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/20 16:40:31 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "exec.h"
#include "ms_error.h"

bool	init_exec(t_exec *exec, t_ast *head, t_token *tks, t_alist *env_ls)
{
	const int	err_fd[2] = {-1, -1};
	const int	cpy_size = 2 * sizeof(int);

	ft_bzero(exec, sizeof(t_exec));
	ft_memcpy(exec->dup_std_fd, err_fd, cpy_size);
	if (!store_std_fd(exec->dup_std_fd))
	{
		ft_memcpy(exec->dup_std_fd, err_fd, cpy_size);
		ft_memcpy(exec->redir_fd, err_fd, cpy_size);
		ms_error(PERROR, NULL, NULL);
		return (false);
	}
	exec->redir_fd[0] = STDIN;
	exec->redir_fd[1] = STDOUT;
	exec->is_child = false;
	exec->head = head;
	exec->tokens = tks;
	exec->env_lst = env_ls;
	return (true);
}

void	free_exec(t_exec *exec)
{
	if (exec->is_child || !apply_std_redirection(exec->dup_std_fd))
		close_redir(exec->dup_std_fd);
	close_redir(exec->redir_fd);
	ft_bzero(exec, sizeof(t_exec));
}
