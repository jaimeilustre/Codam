/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 13:38:52 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/14 17:17:04 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_UTILS_H
# define SIGNAL_UTILS_H

# include <stdbool.h>
# include <signal.h>

extern volatile sig_atomic_t	g_signal;

typedef struct sigaction		t_sigaction;
typedef void					(*t_handler) (int);
typedef void					(*t_sigact) (int, siginfo_t *, void *);

bool	init_sig(t_sigaction *sa, int fl, t_handler handl, t_sigact sigact);
bool	exec_signal_handler(void);
bool	prompt_signal_handler(void);

#endif
