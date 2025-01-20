/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 16:28:47 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/19 07:24:17 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

int	count_lines(const char *file)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
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

char	**read_map_into_array(const char *file)
{
	int		fd;
	int		lines;
	char	*line;
	int		i;
	char	**map;
	size_t	len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	lines = count_lines(file);
	if (lines <= 0)
	{
		close(fd);
		return (NULL);
	}
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
	{
		perror("Error allocating memory");
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
	close (fd);
	return (map);
}

// void	print_map(char **map)
// {
// 	int	i;

// 	if (!map)
// 	{
// 		printf("Map is NULL\n");
// 		return ;
// 	}
// 	i = 0;
// 	while (map[i])
// 	{
// 		printf("Line %d: %s", i, map[i]);
// 		i++;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s <map.ber>\n", argv[0]);
// 		return (1);
// 	}
// 	int	lines = count_lines(argv[1]);
// 	if (lines < 0)
// 	{
// 		fprintf(stderr, "failed to count lines in %s\n", argv[1]);
// 		return (1);
// 	}
// 	printf("the file %s has %d lines.\n", argv[1], lines);
// 	char **map = read_map_into_array(argv[1]);
// 	if (!map)
// 	{
// 		fprintf(stderr, "failed to read map from %s\n", argv[1]);
// 		return (1);
// 	}
// 	printf("Map contents:\n");
// 	print_map(map);
// 	for (int i = 0; map[i]; i++)
// 	{
// 		free(map[i]);
// 	}
// 	free(map);
// 	return (0);
// }
