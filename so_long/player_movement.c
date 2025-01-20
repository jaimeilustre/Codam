/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 07:31:39 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/20 11:29:18 by jaimeilustr   ########   odam.nl         */
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
		map[game->position_y][game->position_x] = '0';
		map[new_y][new_x] = 'P';
		game->position_x = new_x;
		game->position_y = new_y;
		game->move_counter++;
		printf("Move count: %d\n", game->move_counter);
		render_map(game, map);
	}
}

void		event_handler(mlx_key_data_t keydata, void *param)
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

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map.ber>\n", argv[0]);
		return (1);
	}
	char **map = read_map_into_array(argv[1]);
	if (!map)
	{
		fprintf(stderr, "Error: Failed to read map.\n");
		return (1);
	}
	int	collectibles, exits, players;
	if (!check_walls(map) || !check_elements(map, &collectibles, &exits, &players))
	{
		fprintf(stderr, "Error: Invalid map.\n");
		for (int i = 0; map[i]; i++)
			free(map[i]);
		free(map);
		return (1);
	}
	int	player_x, player_y;
	player_position(map, &player_x, &player_y);
	if (!is_path_valid(map, player_x, player_y))
	{
		fprintf(stderr, "Error: no valid path exists");
		for (int i = 0; map[i]; i++)
			free(map[i]);
		free(map);
		return (1);
	}
	printf("Map is valid! Collectibles: %d, Exits: %d, Players: %d\n", collectibles, exits, players);

	t_game	game;
	game.mlx = mlx_init(680, 480, "so_long", true);
	if (!game.mlx)
	{
		fprintf(stderr, "Error: failed to initialize MiniLibx.\n");
		return (1);
	}
	game.map = map;
	
	game.map_width = ft_strlen(game.map[0]);
	game.map_height = 0;
	while (game.map[game.map_height])
		game.map_height++;
	
	starting_position(&game);
	load_images(&game);
	render_map(&game, game.map);
	mlx_key_hook(game.mlx, event_handler, &game);
	mlx_loop(game.mlx);
	for (int i = 0; game.map[i]; i++)
		free(game.map[i]);
	free(game.map);
	return (0);
}
