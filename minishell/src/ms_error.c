/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:50:14 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/22 13:50:34 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"
#include "ms_string.h"
#include "ms_error.h"

#define MS_MESSAGE_SIZE 2048

static t_cstr		g_errors[] = {
	"unknown error",
	"permission denied",
	"command not found",
	"no file or directory called",
	"failed to allocated memory",
	"not a valid identifier",
	"not enough arguments",
	"not set",
	"too many arguments",
	"numeric argument required",
	"is a directory",
	"ambiguous redirect"
};

void	ms_error(int ms_errno, t_str str, t_str arg)
{
	char	message[MS_MESSAGE_SIZE];

	if (ms_errno < 0 || ms_errno > MS_ERROR_MAX)
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
