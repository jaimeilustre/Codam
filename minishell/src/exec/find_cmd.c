/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:19:15 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/20 14:07:18 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"

static bool	try_rel_abs_path(t_str cmd, t_str *out_path)
{
	*out_path = NULL;
	if (*cmd == '/'
		|| ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (*out_path = ft_strdup(cmd), true);
		return (ms_error(PERROR, cmd, NULL), true);
	}
	return (false);
}

static void	clean_up(t_str path, t_str *paths)
{
	free(path);
	free_args(paths);
}

t_str	find_cmd(t_str cmd, t_alist *env_lst)
{
	t_str	cmd_path;
	t_cstr	env_path;
	t_str	*paths;
	t_str	*tmp;

	if (try_rel_abs_path(cmd, &cmd_path))
		return (cmd_path);
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
