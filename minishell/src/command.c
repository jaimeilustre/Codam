/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:19:15 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/13 11:18:38 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"

static void	clear(t_str cmd, t_str *paths)
{
	free(cmd);
	free_split(paths);
}

static bool	try_rel_abs_path(t_str cmd, t_str *out_path)
{
	*out_path = NULL;
	if (*cmd == '/'
		|| ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (*out_path = ft_strdup(cmd), true);
		return (ms_error(PERROR, cmd), true);
	}
	return (false);
}

t_str	find_cmd(t_str cmd)
{
	t_str	cmd_path;
	t_str	env_path;
	t_str	*paths;
	t_str	*tmp;

	if (try_rel_abs_path(cmd, &cmd_path))
		return (cmd_path);
	env_path = getenv("PATH");
	if (env_path == NULL)
		return (NULL);
	cmd_path = ft_calloc(PATH_MAX, sizeof(char));
	paths = ft_split(env_path, ':');
	if (paths == NULL || cmd_path == NULL)
		return (ms_error(NO_ALLOC, NULL), clear(cmd_path, paths), NULL);
	tmp = paths;
	while (*tmp)
	{
		append_to_path(cmd_path, *tmp, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (free_split(paths), cmd_path);
		++tmp;
		*cmd_path = '\0';
	}
	return (ms_error(NO_FILE_DIR, cmd), clear(cmd_path, paths), NULL);
}

void	exe_cmd(t_str cmd, t_str *env)
{
	pid_t	pid;
	t_str	*argv;
	t_str	path_to_cmd;

	argv = ft_split(cmd, ' ');
	if (argv == NULL)
		return ;
	pid = -1;
	path_to_cmd = find_cmd(*argv);
	if (path_to_cmd != NULL)
	{
		pid = fork();
		if (pid == 0 && execve(path_to_cmd, argv, env) == -1)
			ms_error(PERROR, cmd);
		else if (pid == -1)
			ms_error(PERROR, NULL);
		else
			waitpid(pid, NULL, 0);
	}
	clear(path_to_cmd, argv);
	if (pid == 0)
		exit(EXIT_FAILURE);
}
