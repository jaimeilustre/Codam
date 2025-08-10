/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:14:43 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/17 08:05:36 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "pipex.h"

int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		handle_error(filename, "Error opening input file");
		return (-1);
	}
	return (fd);
}

int	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		handle_error(filename, "Error opening output file");
		return (-1);
	}
	return (fd);
}

void	open_files(char **argv, int *input_fd, int *output_fd)
{
	*input_fd = open_input_file(argv[1]);
	*output_fd = open_output_file(argv[4]);
	if (*output_fd == -1)
	{
		if (*input_fd != 1)
			close(*input_fd);
		exit(1);
	}
}
