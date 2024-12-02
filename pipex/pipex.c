/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 15:24:06 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/02 12:18:46 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "pipex.h"

void handle_error(const char *msg)
{
	char	*error_message;

	error_message = strerror(errno);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	write(STDERR_FILENO, "\n", 1);
}

int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		handle_error("Error opening input file");
		exit(1);
	}
	return (fd);
}

int	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		handle_error("Error opening output file");
		exit(1);
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
		{
			free(paths);
			return (NULL);
		}
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
		handle_error("Error splitting command or empty command");
		exit(1);
	}
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free(args);
		exit(127);
	}
	if (execve(cmd_path, args, envp) < 0)
	{
		handle_error("Error executing command");
		free(args);
		free(cmd_path);
		exit(1);
	}
	free(args);
	free(cmd_path);
}

void	create_pipe(int pipe_fd[])
{
	if (pipe(pipe_fd) < 0)
	{
		handle_error("Error creating pipe");
		exit(1);
	}
}

void	first_child(int input_fd, int pipe_fd[], char *cmd, char **envp)
{
	if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		handle_error("Error with dup2 in first child");
		exit(1);
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
		handle_error("Error with dup2 in second child");
		exit(1);
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
	int		status1;
	int		status2;

	input_fd = open_input_file(argv[1]);
	output_fd = open_output_file(argv[4]);
	create_pipe(pipe_fd);
	pid1 = fork();
	if (pid1 < 0)
	{
		handle_error("Error with fork for first child");
		exit(1);
	}
	else if (pid1 == 0)
		first_child(input_fd, pipe_fd, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
	{
		handle_error("Error with fork for second child");
		exit(1);
	}
	else if (pid2 == 0)
		second_child(output_fd, pipe_fd, argv[3], envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(input_fd);
	close(output_fd);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2)) 
        exit(WEXITSTATUS(status2));
    else if (WIFSIGNALED(status2))
        exit(128 + WTERMSIG(status2));
	else
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
	{
		pipex(argv, envp);
		return (1);
	}
	fprintf(stderr, "Invalid number of arguments: %s\n", argv[0]);
	return (1);
}
