/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reading.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 12:09:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/20 17:17:47 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "map_reading.h"

/*Check for a valid file extension*/
void	file_extension(const char *filename)
{
	const char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0
		|| ft_strlen(extension) != 4)
	{
		ft_putendl_fd("Error\nInvalid file extension!", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

/*Count the number of lines from the map*/
int	count_map_lines(const char *file)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	close (fd);
	return (line_count);
}



/*Allocate for a 2D array map file*/
char	**allocate_map(int fd, int lines)
{
	char	**map;
	char	*line;
	int		i;
	size_t	len;

	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
	{
		close (fd);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

/*Create a 2D array map file*/
char	**create_map(const char *file)
{
	int		fd;
	int		lines;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = count_map_lines(file);
	if (lines <= 0)
	{
		close(fd);
		return (NULL);
	}
	map = allocate_map(fd, lines);
	close (fd);
	return (map);
}

// Calculate max width and height of map based on longest lines
// Use those max lengths to allocate for the final map
// Copy map into the final map and if length is shorter than max length,
// then fill the remaining spots with X's for raycasting to ignore

int	max_map_size(char **map)
{
	
}

char	**create_final_map(char **map)
{
	
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	char	**map = create_map(argv[1]);
	
// 	if (argc > 1)
// 	{
// 		int	lines = count_map_lines(argv[1]);
// 		int	i = 0;
// 		while (i < lines)
// 		{
// 			printf("%s\n", map[i]);
// 			i++;
// 		}
// 	}
// 	return (0);
// }





