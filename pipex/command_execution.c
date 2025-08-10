/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_execution.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:20:18 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/17 13:54:44 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	parse_command(cmd, envp, &args, &cmd_path);
	if (execve(cmd_path, args, envp) < 0)
	{
		handle_error(cmd, "Error executing command");
		free_array(args);
		free(cmd_path);
		exit(1);
	}
	free_array(args);
	free(cmd_path);
}

void	first_child(int input_fd, int pipe_fd[], char *cmd, char **envp)
{
	if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		handle_error("dup2", "Error with dup2 in first child");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(input_fd);
		exit(1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(input_fd);
	execute_command(cmd, envp);
}

void	second_child(int output_fd, int pipe_fd[], char *cmd, char **envp)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0
		|| dup2(output_fd, STDOUT_FILENO) < 0)
	{
		handle_error("dup2", "Error with dup2 in second child");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(output_fd);
		exit(1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(output_fd);
	execute_command(cmd, envp);
}
