/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 19:25:50 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/19 06:07:36 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "so_long.h"

bool	check_walls(char **map)
{
	size_t	rows;
	size_t	i;

	rows = 0;
	while (map[rows])
		rows++;
	i = 0;
	while (i < ft_strlen(map[0]))
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (i < rows - 1)
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[0]) - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	check_elements(char **map, int *collectibles, int *exits, int *players)
{
	int	i;
	int	j;
	
	*collectibles = 0;
	*exits = 0;
	*players = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				(*collectibles)++;
			else if (map[i][j] == 'E')
				(*exits)++;
			else if (map[i][j] == 'P')
				(*players)++;
			else if (map[i][j] != '1' && map[i][j] != '0')
				return (false);
			j++;
		}
		i++;
	}
	return (*collectibles > 0 && *exits > 0 && *players == 1);
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
// 	if (!validate_walls(map) || !validate_map_elements(map, &collectibles, &exits, &players))
// 	{
// 		fprintf(stderr, "Error: Invalid map.\n");
// 		return (1);
// 	}
// 	printf("Map is valid! Collectibles: %d, Exits: %d, Players: %d\n", collectibles, exits, players);
// 	for (int i = 0; map[i]; i++)
// 		free(map[i]);
// 	free(map);
// 	return (0);
// }
