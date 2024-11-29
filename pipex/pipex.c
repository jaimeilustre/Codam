/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 15:24:06 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/29 15:25:06 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "pipex.h"

int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

char	*get_command_path(char *cmd, char **envp)
{
	char		*path_env;
	char		**paths;
	char		*full_path;
	struct stat	buffer;
	int			i;

	path_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
		if (!full_path)
			break ;
		sprintf(full_path, "%s/%s", paths[i], cmd);
		if (stat(full_path, &buffer) == 0)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	cmd_path = get_command_path(args[0], envp);
	if (!args || !args[0])
	{
		perror("Error splitting command or empty command");
		exit(EXIT_FAILURE);
	}
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free(args);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, args, envp);
	perror("Error executing command");
	free(cmd_path);
	free (args);
	exit(EXIT_FAILURE);
}


void	create_pipe(int pipe_fd[])
{
	if (pipe(pipe_fd) < 0)
	{
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
}

void	first_child(int input_fd, int pipe_fd[], char *cmd, char **envp)
{
	if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		perror("Error with dup2 in first child");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(input_fd);
	execute_command(cmd, envp);
}

void	second_child(int output_fd, int pipe_fd[], char *cmd, char **envp)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0 || dup2(output_fd, STDOUT_FILENO) < 0)
	{
		perror("Error with dup2 in second child");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(output_fd);
	execute_command(cmd, envp);
}

void	pipex(char **argv, char **envp)
{
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	input_fd = open_input_file(argv[1]);
	output_fd = open_output_file(argv[4]);
	create_pipe(pipe_fd);
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error with fork for first child");
		exit(EXIT_FAILURE);
	}
	else if (pid1 == 0)
		first_child(input_fd, pipe_fd, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error with fork for second child");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
		second_child(output_fd, pipe_fd, argv[3], envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(input_fd);
	close(output_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
	{
		pipex(argv, envp);
		return (EXIT_SUCCESS);
	}
	fprintf(stderr, "Invalid number of arguments: %s\n", argv[0]);
	return (EXIT_FAILURE);
}
