/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 11:52:28 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/25 10:26:03 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "exec.h"
#include "minishell.h"
#include "ms_signals.h"
#include "ms_string.h"
#include "parser.h"

t_str	cmd_prompt(t_cstr prompt)
{
	t_str	cmd;

	cmd = readline(prompt);
	if (cmd == NULL)
		return (rl_clear_history(), NULL);
	else if (is_empty_cmd(cmd))
		*cmd = '\0';
	else
		add_history(cmd);
	return (cmd);
}

static t_token	*check_tokens(t_str cmd, t_exit_code *exit_code)
{
	t_token	*tokens;
	int		syntax_error;

	tokens = create_tokens(cmd, &syntax_error);
	if (tokens == NULL)
	{
		if (syntax_error)
			*exit_code = E_MISS_BLTIN;
		else
			*exit_code = E_GEN_ERR;
	}
	return (tokens);
}

t_exit_code	exec_prompt(t_str cmd, t_alist *env_lst)
{
	t_token		*tokens;
	t_ast		*ast;
	t_exec		exec;
	t_exit_code	exit_code;

	exit_code = E_GEN_ERR;
	tokens = check_tokens(cmd, &exit_code);
	if (tokens == NULL)
		return (exit_code);
	ast = build_ast_tree(tokens, env_lst);
	if (ast != NULL)
	{
		if (init_exec(&exec, ast, tokens, env_lst) && ign_signal_handler())
		{
			exec.cmd = cmd;
			exit_code = exec_node(ast, &exec);
		}
		free_ast(ast);
		free_exec(&exec);
	}
	else if (g_signo == SIGINT)
		exit_code = E_TERM;
	else
		exit_code = E_MISS_BLTIN;
	return (free_token_list(&tokens), exit_code);
}
