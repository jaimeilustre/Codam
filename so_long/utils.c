/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 09:32:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/01/27 17:25:42 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->position_x = x;
				game->position_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	window_size(t_game *game, char **map)
{
	game->window_width = ft_strlen(map[0]) * 64;
	game->window_height = 0;
	while (map[game->window_height])
		game->window_height++;
	game->window_height *= 64;
}
