/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 11:50:57 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/28 12:36:20 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include "ms_string.h"
# include "list.h"
# include "parser.h"

# define RE_MAX_FD 2

typedef struct s_exec
{
	int		wstatus;
	bool	is_child;
	int		redir_fd[2];
	int		dup_std_fd[2];
	t_alist	*env_lst;
	t_str	cmd;
	t_ast	*head;
	t_token	*tokens;
}	t_exec;

/* Execution */

t_exec	*init_exec(t_str cmd, t_ast *head, t_token *tokens, t_alist *env_lst);
void	free_exec(t_exec **exec);

int		get_exit_code(int wstatus);
void	wait_or_kill_child(pid_t cpid, t_exec *exec);
void	exit_process(t_exec *exec);
bool	start_fork(pid_t *cpid, t_exec *exec);

bool	is_rel_abs_path(t_cstr path);
t_str	find_cmd(t_str cmd, t_alist *env_lst);

bool	exec_node(t_ast *node, t_exec *exec);
bool	exec_pipe(t_ast *node, t_exec *exec);
bool	exec_cmd(t_ast *node, t_exec *exec);
int		exec_prompt(t_str cmd, t_alist *env_lst);

/* Redirection */

void	close_redir(int fd[2]);
void	safe_close_fd(int *fd);
bool	redirect_fd(int *fd, int dupfd);
bool	apply_std_redirection(int pipe_fd[2]);
bool	apply_redirection(t_redirect *redir, int redir_fd[2]);
bool	store_std_fd(int new_fd[RE_MAX_FD]);

/* Expansion */

bool	expand_variable(t_strb *sb, t_cstr *var, t_alist *env_lst);
bool	expand_arguments(t_str *args, t_alist *env_lst);

#endif
