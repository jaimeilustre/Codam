/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sig_heredoc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 17:10:38 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/18 11:10:19 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>

#include "libft.h"
#include "minishell.h"
#include "ms_signals.h"

static void	trap_sigint(int signo)
{
	g_signo = signo;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
}

/* Forces readline to exit on ctrl-c */
static int	stop_heredoc(void)
{
	return (0);
}

bool	trap_sigint_heredoc(void)
{
	t_sigaction	sa;

	rl_event_hook = stop_heredoc;
	sa.sa_flags = 0;
	sa.sa_handler = trap_sigint;
	return (
		sigemptyset(&(sa.sa_mask)) != -1
		&& sigaction(SIGINT, &sa, NULL) != -1);
}
