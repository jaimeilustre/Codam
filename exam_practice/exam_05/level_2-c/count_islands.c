/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_islands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/09 15:10:29 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/12 14:10:02 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "count_islands.h"

// static void	flood(t_map *map, int y, int x)
// {
// 	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
// 		return ;
// 	if (map->grid[y][x] != '1')
// 		return ;
// 	map->grid[y][x] = 'x';
// 	flood(map, y + 1, x);
// 	flood(map, y - 1, x);
// 	flood(map, y, x + 1);
// 	flood(map, y, x - 1);
// }

// static int	count_islands(t_map *map)
// {
// 	int	y;
// 	int	x;
// 	int	count = 0;

// 	y = -1;
// 	while (++y < map->height)
// 	{
// 		x = -1;
// 		while (++x < map->width)
// 		{
// 			if (map->grid[y][x] == '1')
// 			{
// 				count++;
// 				flood(map, y, x);
// 			}
// 		}
// 	}
// 	return (count);
// }

// return largest island
static int flood(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (0);
	if (map->grid[y][x] != '1')
		return (0);
	map->grid[y][x] = 'x';
	return (1
		+ flood(map, y + 1, x)
		+ flood(map, y - 1, x)
		+ flood(map, y, x + 1)
		+ flood(map, y, x - 1));
}

static int count_islands(t_map *map)
{
	int y;
	int x;
	int max_size = 0;
	
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->grid[y][x] == '1')
			{
				int size = flood(map, y, x);
				if (size > max_size)
					max_size = size;
			}	
		}
	}
	return (max_size);
}

static void	free_map(t_map *map)
{
	int i = 0;
	while (i < map->height)
		free(map->grid[i++]);
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
	map->grid = malloc(map->height * sizeof(char *));

	// Step 3: Split lines manually 
	row = 0; // current row index in the grid
	start = 0; // marks the beginning of the current line in buf
	for (i = 0; i <= len; i++)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
		{
			// skips empty lines
			if (i == start)
			{
				start = i + 1;
				continue ;
			}
			
			 // allocate enough space for one full line (+1 for null terminator)
			map->grid[row] = malloc(map->width + 1);
			
			// copy characters into the grid
			j = 0;
			while (start < i && j < map->width)
				map->grid[row][j++] = buf[start++];
			map->grid[row][j] = '\0';

			// move to next row
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
		return (write(1, "Error\n", 6), 1);
	n = count_islands(map);

	// essentially itoa/putnbr
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

