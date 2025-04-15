/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:50:14 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/14 15:58:20 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"
#include "ms_string.h"
#include "ms_error.h"

static t_cstr	g_errors[] = {
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
	if (ms_errno < 0 || ms_errno > MS_ERROR_MAX)
		ms_errno = UNKNOWN;
	ft_putstr_fd(MINISHELL ": ", STDERR);
	if (str != NULL)
	{
		ft_putstr_fd(str, STDERR);
		if (arg != NULL)
		{
			ft_putstr_fd(" \'", STDERR);
			ft_putstr_fd(arg, STDERR);
			ft_putchar_fd('\'', STDERR);
		}
		ft_putstr_fd(": ", STDERR);
	}
	if (ms_errno == PERROR)
		ft_putendl_fd(strerror(errno), STDERR);
	else
		ft_putendl_fd((t_str)g_errors[ms_errno], STDERR);
}
