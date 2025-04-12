/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 13:38:52 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/05 21:33:27 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_UTILS_H
# define SIGNAL_UTILS_H

# include <stdbool.h>
# include <signal.h>

typedef struct sigaction	t_sigaction;
typedef void				(*t_handler) (int);
typedef void				(*t_sigact) (int, siginfo_t *, void *);

bool	init_sig(t_sigaction *sa, int fl, t_handler handl, t_sigact sigact);
bool	ign_signal_handler(void);
bool	dfl_signal_handler(void);
bool	prompt_signal_handler(void);

#endif
