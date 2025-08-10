/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 15:24:06 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/17 08:04:23 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char **argv, char **envp)
{
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	open_files(argv, &input_fd, &output_fd);
	create_pipe(pipe_fd);
	pid1 = fork_first_child(input_fd, pipe_fd, argv[2], envp);
	pid2 = fork_second_child(output_fd, pipe_fd, argv[3], envp);
	parent_process_cleanup(input_fd, pipe_fd, output_fd);
	wait_for_children(pid1, pid2);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		handle_error(argv[0], "Invalid number of arguments");
		return (1);
	}
	pipex(argv, envp);
	return (0);
}
