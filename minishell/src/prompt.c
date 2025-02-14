/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 11:52:28 by jboon         #+#    #+#                 */
/*   Updated: 2025/01/27 17:45:52 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"

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
		return (clear_history(), NULL);
	if (!is_empty_cmd(cmd))
		add_history(cmd);
	else
		*cmd = '\0';
	return (cmd);
}
