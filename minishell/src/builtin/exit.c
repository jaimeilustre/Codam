/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/28 14:47:54 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:55:36 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "libft.h"

#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "ms_error.h"
#include "ms_string.h"

static int	str_to_exit(t_cstr exit_str)
{
	t_str	endptr;
	long	exit_code;

	if (exit_str == NULL)
		return (E_SUCCESS);
	errno = 0;
	exit_code = ft_strtol(exit_str, &endptr);
	if (errno == ERANGE || *endptr != '\0')
	{
		ms_error(NUM_ARG_REQ, EXIT_NAME, (t_str)exit_str);
		return (E_MISS_BLTIN);
	}
	else if (exit_code < 0)
		return (((exit_code % 256) + 256) % 256);
	return (exit_code % 256);
}

int	ms_exit(int argc, t_str *argv, void *exec)
{
	t_exit_code	exit_code;
	t_exec		*exe;

	exe = (t_exec *)exec;
	if (!exe->is_child)
		ft_putendl_fd(EXIT_NAME, 1);
	if (argc < 2)
		exit_code = str_to_exit(ms_getenv(exe->env_lst, V_EXIT));
	else if (argc == 2)
		exit_code = str_to_exit(*(argv + 1));
	else
	{
		exit_code = E_MISS_BLTIN;
		ms_error(TOO_N_ARGS, EXIT_NAME, NULL);
	}
	exit_process(exec, exit_code);
	return (E_SUCCESS);
}
