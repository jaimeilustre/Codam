/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 11:52:28 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/18 11:25:31 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "signal_utils.h"
#include "parser.h"
#include "exec.h"

/**
 * @brief Display a new prompt on a new line
 */
static void	clear_prompt(void)
{
	write(STDIN, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/**
 * @brief Use this to catch any signal that should not alter the prompt.
 */
static void	do_nothing(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	interative_mode(int signo)
{
	if (signo == SIGINT)
		clear_prompt();
	else if (signo == SIGQUIT)
		do_nothing();
}

t_str	cmd_prompt(t_cstr prompt)
{
	char	*cmd;

	cmd = readline(prompt);
	if (cmd == NULL)
		return (rl_clear_history(), NULL);
	if (!is_empty_cmd(cmd))
		add_history(cmd);
	else
		*cmd = '\0';
	return (cmd);
}

int	exec_prompt(t_str cmd, t_alist *env_lst)
{
	t_token	*tmp_tokens;
	t_token	*tokens;
	t_ast	*ast;
	t_exec	*exec;
	int		exit_code;

	exit_code = 1;
	tokens = create_tokens(cmd);
	if (tokens != NULL)
	{
		tmp_tokens = tokens;
		ast = build_ast_tree(&tmp_tokens);
		if (ast != NULL)
		{
			exec_signal_handler();
			exec = init_exec(cmd, ast, tokens, env_lst);
			if (exec != NULL && exec_node(ast, exec))
				exit_code = get_exit_code(exec->wstatus);
			free_ast(ast);
			free_exec(&exec);
			prompt_signal_handler();
		}
		free_token_list(&tokens);
	}
	return (exit_code);
}
