/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 12:21:47 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/28 11:46:33 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"

static void	clean_up(t_str path, t_str *paths)
{
	free(path);
	free_args(paths);
}

bool	is_rel_abs_path(t_cstr path)
{
	return (*path == '/'
		|| (ft_strncmp(path, "./", 2) == 0)
		|| (ft_strncmp(path, "../", 3) == 0)
	);
}

// TODO: append_to_path does not tell if the path was fully appended.
t_str	find_cmd(t_str cmd, t_alist *env_lst)
{
	t_str	cmd_path;
	t_cstr	env_path;
	t_str	*paths;
	t_str	*tmp;

	env_path = ms_getenv(env_lst, "PATH");
	if (env_path == NULL)
		return (NULL);
	cmd_path = ft_calloc(PATH_MAX, sizeof(char));
	paths = ft_split(env_path, ':');
	if (paths == NULL || cmd_path == NULL)
		return (ms_error(PERROR, NULL, NULL), clean_up(cmd_path, paths), NULL);
	tmp = paths;
	while (*tmp)
	{
		append_to_path(cmd_path, *tmp, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (free_args(paths), cmd_path);
		++tmp;
		*cmd_path = '\0';
	}
	return (ms_error(NO_FILE_DIR, cmd, NULL), clean_up(cmd_path, paths), NULL);
}
