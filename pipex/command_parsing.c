/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:16:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/17 08:05:27 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(char *cmd, char **envp)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (search_in_paths(cmd, envp));
}

char	*search_in_paths(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*full_path;

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = try_paths(cmd, paths);
	free_array(paths);
	return (full_path);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*try_paths(char *cmd, char **paths)
{
	char	*full_path;
	int		i;
	size_t	full_path_size;

	i = 0;
	while (paths[i])
	{
		full_path_size = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(full_path_size);
		if (!full_path)
			break ;
		ft_strlcpy(full_path, paths[i], full_path_size);
		ft_strlcat(full_path, "/", full_path_size);
		ft_strlcat(full_path, cmd, full_path_size);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	parse_command(char *cmd, char **envp, char ***args, char **cmd_path)
{
	*args = ft_split(cmd, ' ');
	*cmd_path = get_command_path(*args[0], envp);
	if (!*args || !args[0])
	{
		handle_error(cmd, "Error splitting command or empty command");
		free_array(*args);
		exit(1);
	}
	if (!*cmd_path)
	{
		handle_error(cmd, "Command not found");
		free_array(*args);
		exit(127);
	}
}
