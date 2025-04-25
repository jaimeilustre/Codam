/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_prompt.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/19 15:43:26 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:18:19 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>

#include "ms_signals.h"

/**
 * @brief Display a new prompt on a new line
 */
static void	clear_prompt(void)
{
	rl_done = 1;
}

/**
 * @brief Use this to catch any signal that should not alter the prompt.
 */
static void	do_nothing(void)
{
	rl_on_new_line();
	rl_redisplay();
}

static void	interative_mode(int signo)
{
	g_signo = signo;
	if (signo == SIGINT)
		clear_prompt();
	else if (signo == SIGQUIT)
		do_nothing();
}

bool	trap_prompt_signals(void)
{
	t_sigaction	sa;

	return (init_sig(&sa, 0, interative_mode, NULL));
}
