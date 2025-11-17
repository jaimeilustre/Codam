/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_islands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/09 15:10:29 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/17 20:28:23 by jaimeilustr   ########   odam.nl         */
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

// static void flood(t_map *map, int y, int x)
// {
// 	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
// 		return ;
// 	if (map->grid[y][x] != 'X')
// 		return ;
// 	map->grid[y][x] = 'x';
// 	flood(map, y + 1, x);
// 	flood(map, y - 1, x);
// 	flood(map, y, x + 1);
// 	flood(map, y, x - 1);
// }

// static int count_islands(t_map *map)
// {	
// 	int y;
// 	int x;
// 	int count = 0;
	
// 	y = -1;
// 	while (++y < map->height)
// 	{
// 		x = -1;
// 		while (++x < map->width)
// 		{
// 			if (map->grid[y][x] == 'X')
// 			{
// 				count++;
// 				flood(map, y, x);
// 			}
// 		}
// 	}
// 	return (count);
// }


static void flood(t_map *map, int y, int x, char id)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->grid[y][x] != 'X')
		return ;
	map->grid[y][x] = id;
	flood(map, y + 1, x, id);
	flood(map, y - 1, x, id);
	flood(map, y, x + 1, id);
	flood(map, y, x - 1, id);
}

static void label_islands(t_map *map)
{	
	int y;
	int x;
	char id = '0';
	
	y = 0;
	while (++y < map->height)
	{
		x = 0;
		while (++x < map->width)
		{
			if (map->grid[y][x] == 'X')
			{
				flood(map, y, x, id);
				id++;
			}
		}
	}
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

	label_islands(map);
	print_map(*map);
	free_map(map);
	free(map);
	return (0);		
}

