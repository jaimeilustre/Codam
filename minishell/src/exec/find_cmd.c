/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 12:21:47 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/10 11:01:15 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/stat.h>

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"

static t_str	*get_paths(t_alist *env_lst)
{
	t_cstr	env_path;

	env_path = ms_getenv(env_lst, "PATH");
	if (env_path == NULL)
		return (NULL);
	return (ft_split(env_path, ':'));
}

static t_str	get_cmd_path(t_str *paths, t_cstr cmd)
{
	t_str		cmd_path;
	t_path		found_path[PATH_MAX];
	struct stat	statbuf;

	cmd_path = ft_calloc(PATH_MAX, sizeof(char));
	if (cmd_path == NULL)
		return (NULL);
	ft_bzero(found_path, PATH_MAX);
	while (*paths)
	{
		append_to_path(cmd_path, *paths, cmd);
		if (stat(cmd_path, &statbuf) == 0 && (statbuf.st_mode & S_IFDIR) == 0)
		{
			if ((statbuf.st_mode & S_IXUSR) == S_IXUSR)
				return (cmd_path);
			else if (*found_path == '\0')
				ft_strlcpy(found_path, cmd_path, PATH_MAX);
		}
		*cmd_path = '\0';
		++paths;
	}
	if (*found_path == '\0')
		return (free(cmd_path), NULL);
	ft_strlcpy(cmd_path, found_path, PATH_MAX);
	return (cmd_path);
}

bool	is_rel_abs_path(t_cstr path)
{
	return (*path == '/'
		|| (ft_strncmp(path, "./", 2) == 0)
		|| (ft_strncmp(path, "../", 3) == 0)
	);
}

t_str	find_cmd(t_str cmd, t_alist *env_lst)
{
	t_str	cmd_path;
	t_str	*paths;

	paths = get_paths(env_lst);
	if (paths == NULL)
		return (ms_error(PERROR, NULL, NULL), NULL);
	cmd_path = get_cmd_path(paths, cmd);
	if (cmd_path == NULL)
		ms_error(NO_CMD, cmd, NULL);
	free_args(paths);
	return (cmd_path);
}
