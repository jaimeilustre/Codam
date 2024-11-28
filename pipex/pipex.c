/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 15:24:06 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/28 15:41:21 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
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
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	
	args = ft_split(cmd, ' ');
	if (!args)
	{
		perror("Error splitting command");
		exit(EXIT_FAILURE);
	}
	execve(args[0], args, envp);
	perror("Error executing command");
	exit(EXIT_FAILURE);
}

void	create_pipe(int pipe_fd[])
{
	if(pipe(pipe_fd) < 0)
	{
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
}

void	first_child_process(int input_fd, int pipe_fd[], char *cmd, char **envp)
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

void	second_child_process(int output_fd, int pipe_fd[], char *cmd, char **envp)
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
		first_child_process(input_fd, pipe_fd, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error with fork for second child");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
		second_child_process(output_fd, pipe_fd, argv[3], envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(input_fd);
	close(output_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
