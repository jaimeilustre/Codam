/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:14:43 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/16 15:21:22 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
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
