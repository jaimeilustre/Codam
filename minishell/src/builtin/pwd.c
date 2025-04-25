/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 11:37:04 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:55:42 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#include "libft.h"

#include "exec.h"
#include "minishell.h"
#include "ms_error.h"

int	pwd(int argc, t_str *argv, void *env_lst)
{
	t_path	path[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)env_lst;
	if (getcwd(path, PATH_MAX) == NULL)
		return (ms_error(PERROR, "pwd", NULL), E_GEN_ERR);
	ft_putendl_fd(path, STDOUT);
	return (E_SUCCESS);
}
