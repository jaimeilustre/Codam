/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_management.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:22:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/17 08:05:47 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

void	create_pipe(int pipe_fd[])
{
	if (pipe(pipe_fd) < 0)
	{
		handle_error("pipe", "Error creating pipe");
		exit(1);
	}
}

pid_t	fork_first_child(int input_fd, int *pipe_fd, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		handle_error("fork", "Error with fork for first child");
		exit(1);
	}
	else if (pid == 0)
		first_child(input_fd, pipe_fd, cmd, envp);
	return (pid);
}

pid_t	fork_second_child(int output_fd, int *pipe_fd, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		handle_error("fork", "Error with fork for first child");
		exit(1);
	}
	else if (pid == 0)
		second_child(output_fd, pipe_fd, cmd, envp);
	return (pid);
}

void	parent_process_cleanup(int input_fd, int pipe_fd[], int output_fd)
{
	if (input_fd != 1)
		close(input_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(output_fd);
}

void	wait_for_children(pid_t pid1, pid_t pid2)
{
	int	status;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	exit(1);
}
