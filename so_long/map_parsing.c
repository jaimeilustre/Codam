/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 16:28:47 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/27 17:29:20 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "so_long.h"

int	count_lines(const char *file)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		lines++;
		line = get_next_line(fd);
	}
	close (fd);
	return (lines);
}

char	**read_lines_from_file(int fd, int lines)
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

char	**read_map_into_array(const char *file)
{
	int		fd;
	int		lines;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = count_lines(file);
	if (lines <= 0)
	{
		close(fd);
		return (NULL);
	}
	map = read_lines_from_file(fd, lines);
	close (fd);
	return (map);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**copy_map(char **map)
{
	int		rows;
	char	**map_copy;
	int		i;

	rows = 0;
	while (map[rows])
		rows++;
	map_copy = malloc((rows + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[rows] = NULL;
	return (map_copy);
}
