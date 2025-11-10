/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_islands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/09 15:10:29 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/09 19:50:37 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "count_islands.h"

static void	flood(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->grid[y][x] != '1')
		return ;
	map->grid[y][x] = 'x';
	flood(map, y + 1, x);
	flood(map, y - 1, x);
	flood(map, y, x + 1);
	flood(map, y, x - 1);
}

static int	count_islands(t_map *map)
{
	int	y;
	int	x;
	int	count = 0;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->grid[y][x] == '1')
			{
				count++;
				flood(map, y, x);
			}
		}
	}
	return (count);
}

static void	free_map(t_map *map)
{
	int i = map->height;
	while (i--)
		free(map->grid[i]);
	free(map->grid);
}

static t_map	*read_map(char *file)
{
	int		fd;
	int		len;
	char	buf[10000];
	t_map	*map;
	int		i, j, row, start;

	fd = open(file, O_RDONLY);
	if (fd < 0 || (len = read(fd, buf, 9999)) <= 0)
		return (NULL);
	close(fd);
	buf[len] = '\0';

	// Step 1: Count lines and width
	map = malloc(sizeof(t_map));
	map->height = 0;
	map->width = 0;
	for (i = 0; i < len; i++)
	{
		if (buf[i] == '\n')
			map->height++;
		else if (map->height == 0)
			map->width++;
	}
	if (buf[len - 1] != '\n') // last line without newline
		map->height++;

	// Step 2: Allocate grid
	map->grid = malloc(sizeof(char *) * map->height);

	// Step 3: Split lines manually 
	row = 0;
	start = 0;
	for (i = 0; i <= len; i++)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
		{
			map->grid[row] = malloc(map->width + 1);
			j = 0;
			while (start < i && j < map->width)
				map->grid[row][j++] = buf[start++];
			map->grid[row][j] = '\0';
			row++;
			start = i + 1;
		}
	}
	return (map);
}

int main(int argc, char **argv)
{
	t_map *map;
	int		n;
	char	buf[12];
	int		i;

	if (argc < 2 || !(map = read_map(argv[1])))
		return (write(1, "Error\n", 6), 0);
	n = count_islands(map);
	i = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n)
	{
		buf[i++] = n % 10 + '0';
		n /= 10;
	}
	while (i--)
		write (1, &buf[i], 1);
	write (1, "\n", 1);
	free_map(map);
	free(map);
	return (0);
}

