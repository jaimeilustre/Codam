/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 07:31:39 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/27 17:23:25 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	allowed_movements(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return (false);
	return (game->map[y][x] == '0' || game->map[y][x] == 'C'
		|| game->map[y][x] == 'E');
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectibles--;
		ft_printf("Collectible collected! Remaining: %d\n", game->collectibles);
	}
}

void	handle_exit(t_game *game)
{
	if (game->collectibles == 0)
	{
		ft_printf("You win! Total moves: %d\n", game->move_counter);
		mlx_close_window(game->mlx);
		return ;
	}
	else
		ft_putendl_fd("Collect all items!", STDOUT_FILENO);
}

void	move_player(t_game *game, int dx, int dy, char **map)
{
	int			new_x;
	int			new_y;

	new_x = game->position_x + dx;
	new_y = game->position_y + dy;
	if (allowed_movements(game, new_x, new_y))
	{
		if (game->map[game->position_y][game->position_x] == 'E')
			game->map[game->position_y][game->position_x] = 'E';
		else
			game->map[game->position_y][game->position_x] = '0';
		if (game->map[new_y][new_x] == 'C')
		{
			handle_collectible(game, new_x, new_y);
			game->map[new_y][new_x] = '0';
		}
		game->position_x = new_x;
		game->position_y = new_y;
		game->move_counter++;
		ft_printf("Move count: %d\n", game->move_counter);
		if (game->map[new_y][new_x] == 'E')
			handle_exit(game);
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
