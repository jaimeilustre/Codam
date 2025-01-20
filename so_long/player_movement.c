/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 07:31:39 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/20 17:19:47 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <MLX42/MLX42.h>
#include "so_long.h"

void	starting_position(t_game *game)
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

bool	allowed_movements(char **map, int x, int y, int map_width, int map_height)
{
	if (y < 0 || y >= map_height || x < 0 || x >= map_width)
		return (false);
	return (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'E');
}

void	move_player(t_game *game, int dx, int dy, char **map)
{
	int	new_x;
	int	new_y;

	new_x = game->position_x + dx;
	new_y = game->position_y + dy;
	if (allowed_movements(map, new_x, new_y, game->map_width, game->map_height))
	{
		if (game->map[game->position_y][game->position_x] != 'E')
			game->map[game->position_y][game->position_x] = '0';
		if (game->map[new_y][new_x] == 'C')
		{
			game->collectibles--;
			printf("Collectible collected! Remaining: %d\n", game->collectibles);
		}
		if (game->map[new_y][new_x] == 'E')
		{
			if (game->collectibles == 0)
			{
				printf("You win! Total moves: %d\n", game->move_counter);
				mlx_close_window(game->mlx);
				return ;
			}
			else
			{
				printf("Collect all items before exiting\n");
				return ;
			}
		}
		game->position_x = new_x;
		game->position_y = new_y;
		game->map[new_y][new_x] = 'P';
		game->move_counter++;
		printf("Move count: %d\n", game->move_counter);
		render_map(game, map);
	}
}

void	event_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_player(game, 0, -1, game->map);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_player(game, -1, 0, game->map);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_player(game, 0, 1, game->map);
	else if(keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_player(game, 1, 0, game->map);
}
