/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_validation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 06:10:47 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/20 08:32:27 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "so_long.h"

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

void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y][x] || map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

bool	is_path_valid(char **map, int player_x, int player_y)
{
	char	**map_copy;
	int		y;
	int		x;
	int		i;

	map_copy = copy_map(map);
	if (!map_copy)
		return (false);
	// Flood-fill to check if all collectibles are reachable
	flood_fill(map_copy, player_x, player_y);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' && map_copy[y][x] != 'X')
			{
				// Collectible is unreachable
				i = 0;
				while (map_copy[i])
				{
					free(map_copy[i]);
					i++;
				}
				free(map_copy);
				return (false);
			}
			x++;
		}
		y++;
	}
	// Replace all collectibles with walkable tiles
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				map_copy[y][x] = '0';
			x++;
		}
		y++;
	}
	// Flood-fill to check if the exit is reachable
	flood_fill(map_copy, player_x, player_y);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E' && map_copy[y][x] != 'X')
			{
				// Exit is unreachable
				i = 0;
				while (map_copy[i])
				{
					free(map_copy[i]);
					i++;
				}
				free(map_copy);
				return (false);
			}
			x++;
		}
		y++;
	}
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (true);
}

void	player_position(char **map, int *player_x, int *player_y)
{
	int	y;
	int	x;
	
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				*player_x = x;
				*player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s <map.ber>\n", argv[0]);
// 		return (1);
// 	}
// 	char **map = read_map_into_array(argv[1]);
// 	if (!map)
// 	{
// 		fprintf(stderr, "Error: Failed to read map.\n");
// 		return (1);
// 	}
// 	int	collectibles, exits, players;
// 	if (!check_walls(map) || !check_elements(map, &collectibles, &exits, &players))
// 	{
// 		fprintf(stderr, "Error: Invalid map.\n");
// 		for (int i = 0; map[i]; i++)
// 			free(map[i]);
// 		free(map);
// 		return (1);
// 	}
// 	int	player_x, player_y;
// 	find_player(map, &player_x, &player_y);
// 	if (!is_path_valid(map, player_x, player_y))
// 	{
// 		fprintf(stderr, "Error: no valid path exists");
// 		for (int i = 0; map[i]; i++)
// 			free(map[i]);
// 		free(map);
// 		return (1);
// 	}
// 	printf("Map is valid! Collectibles: %d, Exits: %d, Players: %d\n", collectibles, exits, players);
// 	for (int i = 0; map[i]; i++)
// 		free(map[i]);
// 	free(map);
// 	return (0);
// }
