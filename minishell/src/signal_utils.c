/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 13:29:08 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/18 11:08:28 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"
#include "signal_utils.h"
#include "libft.h"

volatile sig_atomic_t	g_signal = 0;

static void	catch_signals(int signo)
{
	g_signal = signo;
}

bool	exec_signal_handler(void)
{
	t_sigaction	sa;

	g_signal = 0;
	return (init_sig(&sa, 0, catch_signals, NULL));
}

bool	prompt_signal_handler(void)
{
	t_sigaction	sa;

	g_signal = 0;
	return (init_sig(&sa, 0, interative_mode, NULL));
}

bool	init_sig(t_sigaction *sa, int flag, t_handler handl, t_sigact sigact)
{
	sa->sa_flags = flag;
	if (handl != NULL)
		sa->sa_handler = handl;
	else
		sa->sa_sigaction = sigact;
	return (
		sigemptyset(&(sa->sa_mask)) != -1
		&& sigaction(SIGINT, sa, NULL) != -1
		&& sigaction(SIGQUIT, sa, NULL) != -1
		&& sigaction(SIGTERM, sa, NULL) != -1
	);
}
