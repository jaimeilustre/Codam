/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 11:50:57 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/14 18:28:24 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include "ms_string.h"
# include "list.h"
# include "parser.h"

# define RE_MAX_FD 2

typedef enum e_exit_code
{
	E_SUCCESS = 0,			/* Program executed successfully without errors */
	E_GEN_ERR = 1,			/* Catch-all exit code */
	E_MISS_BLTIN = 2,		/* Improper use of shell builtins or syntax */
	E_CMD_NO_PERM = 126,	/* Command found but could not be executed */
	E_CMD_NOT_FOUND = 127,	/* Command not found in sytem's PATH */
	E_INV_ARG = 128,		/* Script exits with an invalid argument */
	E_TERM = 130,			/* Script terminated by Control-C (SIGINT) */
	E_NO_BLTIN = 256,		/* No builtin found */
}	t_exit_code;

typedef struct s_exec
{
	bool	is_child;
	int		redir_fd[2];
	int		dup_std_fd[2];
	t_alist	*env_lst;
	t_str	cmd;
	t_ast	*head;
	t_token	*tokens;
}	t_exec;

typedef struct s_exp
{
	t_strb	sb;
	int		sb_off;
	t_alist	ls;
	int		ls_off;
}	t_exp;

typedef enum e_needle
{
	N_START,
	N_MID,
	N_END,
}	t_needle;

typedef t_str	(*t_strstr)(t_cstr, t_cstr);

/* Execution */

t_exec		*init_exec(t_str cmd, t_ast *head, t_token *tkns, t_alist *env_lst);
void		free_exec(t_exec **exec);
t_exit_code	get_exit_code(int wstatus);
void		store_exit_code(t_alist *env_lst, t_exit_code exit_code);
t_exit_code	wait_on_child(pid_t cpid);
void		exit_process(t_exec *exec, t_exit_code exit_code);
bool		start_fork(pid_t *cpid, t_exec *exec);
bool		is_rel_abs_path(t_cstr path);
t_str		find_cmd(t_str cmd, t_alist *env_lst);
t_exit_code	exec_node(t_ast *node, t_exec *exec);
t_exit_code	exec_pipe(t_ast *node, t_exec *exec);
t_exit_code	exec_cmd(t_ast *node, t_exec *exec);
t_exit_code	exec_prompt(t_str cmd, t_alist *env_lst);

/* Redirection */

void		close_redir(int fd[2]);
void		safe_close_fd(int *fd);
bool		redirect_fd(int *fd, int dupfd);
bool		apply_std_redirection(int pipe_fd[2]);
bool		apply_redirection(t_redirect *redir, int dir_fd[2], t_alist *ev_ls);
bool		store_std_fd(int new_fd[RE_MAX_FD]);

/* Expansion */

bool		any_file(t_cstr wildcard, t_cstr name);
t_cstr		next_token(t_cstr arg, t_cstr tokens);
t_cstr		consume_chars(t_cstr str, const char c);
bool		has_strstr(t_cstr *str, t_cstr ptrn, t_strstr strstr, t_needle ndl);
void		free_exp(t_exp *exp);
void		filter_entries(t_cstr pattern, t_exp *exp, t_needle ndl);
bool		expand_wildcard(t_cstr *ch, t_exp *exp);
bool		expand_var_wildcards(int curr, t_exp *exp);
bool		expand_variable(t_strb *sb, t_cstr *var, t_alist *env_lst);
int			expand_arg(t_cstr arg, t_exp *exp, t_alist *env_lst);
bool		expand_argv(t_str *argv, t_alist *env_lst, t_alist *ls);

#endif
