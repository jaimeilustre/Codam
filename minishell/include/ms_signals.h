/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_signals.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 13:38:52 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/19 16:19:38 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# include <stdbool.h>
# include <signal.h>

extern volatile sig_atomic_t	g_signo;

typedef struct sigaction		t_sigaction;
typedef void					(*t_handler) (int);
typedef void					(*t_sigact) (int, siginfo_t *, void *);

bool	init_sig(t_sigaction *sa, int fl, t_handler handl, t_sigact sigact);
bool	ign_signal_handler(void);
bool	dfl_signal_handler(void);
bool	trap_sigint_heredoc(void);
bool	trap_prompt_signals(void);

#endif
