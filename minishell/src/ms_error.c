/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:50:14 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/13 11:14:35 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"
#include "ms_string.h"
#include "ms_error.h"

static t_cstr	g_errors[] = {
	"Unknown error",
	"Permission denied",
	"Command not found",
	"No file or directory called",
	"Malloc fail"
};

void	ms_error(int ms_errno, t_str str)
{
	if (ms_errno < 0 || ms_errno > MS_ERROR_MAX)
		ms_errno = UNKNOWN;
	ft_putstr_fd(MINISHELL ": ", STDERR);
	if (ms_errno == PERROR)
		ft_putstr_fd(strerror(errno), STDERR);
	else
		ft_putstr_fd((t_str)g_errors[ms_errno], STDERR);
	if (str != NULL)
	{
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(str, STDERR);
	}
}
