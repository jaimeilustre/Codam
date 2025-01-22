/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 07:31:39 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/22 15:16:23 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"

bool	allowed_movements(t_map_info *map_info, int x, int y)
{
	if (y < 0 || y >= map_info->height || x < 0 || x >= map_info->width)
		return (false);
	return (map_info->map[y][x] == '0' || map_info->map[y][x] == 'C'
		|| map_info->map[y][x] == 'E');
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectibles--;
		ft_putstr_fd("Collectible collected! Remaining: ", STDOUT_FILENO);
		ft_putnbr_fd(game->collectibles, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	handle_exit(t_game *game)
{
	if (game->collectibles == 0)
	{
		ft_putstr_fd("You win! Total moves: ", STDOUT_FILENO);
		ft_putnbr_fd(game->move_counter, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		mlx_close_window(game->mlx);
	}
	else
		ft_putendl_fd("Collect all items before exiting!", STDOUT_FILENO);
}

void	move_player(t_game *game, int dx, int dy, char **map)
{
	int			new_x;
	int			new_y;
	t_map_info	map_info;

	map_info.map = map;
	map_info.width = game->map_width;
	map_info.height = game->map_height;
	new_x = game->position_x + dx;
	new_y = game->position_y + dy;
	if (allowed_movements(&map_info, new_x, new_y))
	{
		if (game->map[game->position_y][game->position_x] != 'E')
			game->map[game->position_y][game->position_x] = '0';
		handle_collectible(game, new_x, new_y);
		if (game->map[new_y][new_x] == 'E')
		{
			handle_exit(game);
			return ;
		}
		game->position_x = new_x;
		game->position_y = new_y;
		game->map[new_y][new_x] = 'P';
		game->move_counter++;
		ft_putstr_fd("Move count: ", STDOUT_FILENO);
		ft_putnbr_fd(game->move_counter, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
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
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_player(game, 1, 0, game->map);
}
