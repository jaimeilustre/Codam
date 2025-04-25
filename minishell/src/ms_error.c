/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:50:14 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 18:40:32 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>

#include "libft.h"

#include "minishell.h"
#include "ms_error.h"
#include "ms_string.h"

#define MS_MESSAGE_SIZE 2048

static t_cstr		g_errors[PERROR] = {
[UNKNOWN] = "unknown error",
[NO_PERM] = "permission denied",
[NO_CMD] = "command not found",
[INVALID_ID] = "not a valid identifier",
[NO_ENV_VAR] = "not set",
[TOO_N_ARGS] = "too many arguments",
[NUM_ARG_REQ] = "numeric argument required",
[IS_DIR] = "is a directory",
[AMB_REDIR] = "ambiguous redirect"
};

void	ms_error(int ms_errno, t_str str, t_str arg)
{
	char	message[MS_MESSAGE_SIZE];

	if (ms_errno < UNKNOWN || ms_errno > PERROR)
		ms_errno = UNKNOWN;
	ft_bzero(message, 1);
	ft_strlcat(message, MINISHELL ": ", MS_MESSAGE_SIZE);
	if (str != NULL)
	{
		ft_strlcat(message, str, MS_MESSAGE_SIZE);
		if (arg != NULL)
		{
			ft_strlcat(message, ": ", MS_MESSAGE_SIZE);
			ft_strlcat(message, arg, MS_MESSAGE_SIZE);
		}
		ft_strlcat(message, ": ", MS_MESSAGE_SIZE);
	}
	if (ms_errno == PERROR)
		ft_strlcat(message, strerror(errno), MS_MESSAGE_SIZE);
	else
		ft_strlcat(message, g_errors[ms_errno], MS_MESSAGE_SIZE);
	ft_putendl_fd(message, STDERR);
}
