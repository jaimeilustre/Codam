/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 19:25:50 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/21 15:31:50 by jilustre      ########   odam.nl         */
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
	return (*collectibles > 0 && *exits == 1 && *players == 1);
}
