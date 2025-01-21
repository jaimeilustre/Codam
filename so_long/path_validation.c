/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_validation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 06:10:47 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/21 09:53:41 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "so_long.h"

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

bool	check_collectibles(char **map, char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' && map_copy[y][x] != 'X')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_exit(char **map, char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E' && map_copy[y][x] != 'X')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

void	modify_collectibles(char **map, char **map_copy)
{
	int	y;
	int	x;

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
}

bool	is_path_valid(char **map, int player_x, int player_y)
{
	char	**map_copy;

	map_copy = copy_map(map);
	if (!map_copy)
		return (false);
	flood_fill(map_copy, player_x, player_y);
	if (!check_collectibles(map, map_copy))
	{
		free_map(map_copy);
		return (false);
	}
	modify_collectibles(map, map_copy);
	flood_fill(map_copy, player_x, player_y);
	if (!check_exit(map, map_copy))
	{
		free_map(map_copy);
		return (false);
	}
	free_map(map_copy);
	return (true);
}
