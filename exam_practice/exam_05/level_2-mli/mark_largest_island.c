/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mark_largest_island.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/17 20:50:42 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/17 20:52:45 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_map
{
	int height;
	int width;
	char **grid;
	
}	t_map;

static int flood_count(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (0);
	if (map->grid[y][x] != 'X')
		return (0);

	map->grid[y][x] = 'x'; // temporary mark
	return (1
		+ flood_count(map, y + 1, x)
		+ flood_count(map, y - 1, x)
		+ flood_count(map, y, x + 1)
		+ flood_count(map, y, x - 1));
}

static void flood_restore(t_map *map)
{
	for (int y = 0; y < map->height; y++)
		for (int x = 0; x < map->width; x++)
			if (map->grid[y][x] == 'x')
				map->grid[y][x] = 'X';
}

static void flood_mark(t_map *map, int y, int x, char mark)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return;
	if (map->grid[y][x] != 'X')
		return;
	map->grid[y][x] = mark;
	flood_mark(map, y + 1, x, mark);
	flood_mark(map, y - 1, x, mark);
	flood_mark(map, y, x + 1, mark);
	flood_mark(map, y, x - 1, mark);
}

static void find_and_mark_largest(t_map *map)
{
	int max_size = 0;
	int best_y = -1;
	int best_x = -1;

	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			if (map->grid[y][x] == 'X')
			{
				int size = flood_count(map, y, x);

				if (size > max_size)
				{
					max_size = size;
					best_y = y;
					best_x = x;
				}
			}
		}
	}

	flood_restore(map);                  // restore all 'x' back to 'X'
	flood_mark(map, best_y, best_x, '1'); // or 'L' or whatever
}



static void free_map(t_map *map)
{
	int i = 0;
	while (i < map->height)
			free(map->grid[i++]);
	free(map->grid);
}

static void print_map(t_map map)
{
	for (int y = 0; y < map.height; y++)
	{
		for (int x = 0; x < map.width; x++)
			write(1, &map.grid[y][x], 1);
		write(1, "\n", 1);
	}
}

static t_map	*read_map(char *file)
{
	int fd;
	int len;
	char buf[10000];
	t_map *map;
	int i, j, row, start, line_len;

	fd = open(file, O_RDONLY);
	if (fd < 0 || (len = read(fd, buf, 9999)) <= 0)
		return (NULL);
	close(fd);
	buf[len] = '\0';

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
	if (buf[len - 1] != '\n')
		map->height++;
	
	map->grid = malloc(map->height * sizeof(char *));
	if (!map->grid)
		return (free(map), NULL);

	for (int k = 0; k < map->height; k++)
   		map->grid[k] = NULL;
	
	row = 0;
	start = 0;
	for (int i = 0; i <= len; i++)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
		{
			line_len = i - start;
			
			if (line_len == 0)
			{
				int k = i;
				while (buf[k] == '\n')
					k++;
				
				if (buf[k] == '\0')
					break ;
					
				return (free_map(map), free(map), NULL);
			}
			
			if (line_len != map->width)
				return (free_map(map), free(map), NULL);
			
			map->grid[row] = malloc(map->width + 1);
			if (!map->grid[row])
				return (free_map(map), free(map), NULL);
			
			j = 0;
			while (start < i)
			{
				char c = buf[start++];
				if (c != '.' && c != 'X')
					return (free_map(map), free(map), NULL);
				map->grid[row][j++] = c;
			}
			map->grid[row][j] = '\0';
			row++;
			start = i + 1;
		}
	}
	if (row != map->height)
		return (free_map(map), free(map), NULL);
	return (map);
}

int main(int argc, char **argv)
{
	// int i;
	// int n;
	// char buf[12];
	t_map *map;

	if (argc < 2 || !(map = read_map(argv[1])))
		return (write(1, "Map Error\n", 10),1);
	// n = count_islands(map);
	// i = 0;
	// if (n == 0)
	// 	buf[i++] = '0';
	// while (n)
	// {
	// 	buf[i++] = n % 10 + '0';
	// 	n /= 10;
	// }
	// while (i--)
	// 	write(1, &buf[i], 1);
	// write (1, "\n", 1);

	find_and_mark_largest(map);
	print_map(*map);
	free_map(map);
	free(map);
	return (0);		
}