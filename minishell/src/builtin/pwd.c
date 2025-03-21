/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 11:37:04 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/10 13:59:46 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_error.h"
#include "libft.h"

int	pwd(int argc, t_str *argv, t_alist *env_lst)
{
	t_path	path[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)env_lst;
	if (getcwd(path, PATH_MAX) == NULL)
		return (ms_error(PERROR, "pwd", NULL), 1);
	ft_putendl_fd(path, STDOUT);
	return (0);
}
