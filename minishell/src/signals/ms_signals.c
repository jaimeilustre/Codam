/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_signals.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 13:29:08 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/19 20:54:58 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"
#include "ms_signals.h"
#include "libft.h"

volatile sig_atomic_t	g_signo = 0;

static void	sig_ign(int signo)
{
	g_signo = signo;
}

bool	dfl_signal_handler(void)
{
	t_sigaction	sa;

	g_signo = 0;
	return (init_sig(&sa, 0, SIG_DFL, NULL));
}

bool	ign_signal_handler(void)
{
	t_sigaction	sa;

	g_signo = 0;
	return (init_sig(&sa, 0, sig_ign, NULL));
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
