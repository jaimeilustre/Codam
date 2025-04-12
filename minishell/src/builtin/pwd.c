/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 11:37:04 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/09 01:28:34 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "ms_error.h"
#include "exec.h"

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
