/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 13:29:08 by jboon         #+#    #+#                 */
/*   Updated: 2025/01/27 14:14:04 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "signal_utils.h"

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
	);
}
