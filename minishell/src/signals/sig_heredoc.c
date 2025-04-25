/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_heredoc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 17:10:38 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:18:07 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>

#include "ms_signals.h"

static void	trap_sigint(int signo)
{
	g_signo = signo;
	rl_done = 1;
}

bool	trap_sigint_heredoc(void)
{
	t_sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = trap_sigint;
	return (
		sigemptyset(&(sa.sa_mask)) != -1
		&& sigaction(SIGINT, &sa, NULL) != -1);
}
