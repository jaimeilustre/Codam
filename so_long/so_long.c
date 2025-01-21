/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 17:11:09 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/21 16:18:31 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <MLX42/MLX42.h>
#include "so_long.h"

int	handle_error(char **map)
{
	if (!map)
	{
		ft_putendl_fd("Error\nNo/empty file!\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_map(char **map, int *collectibles, int *exits, int *players)
{
	if (!check_walls(map) || !check_elements(map, collectibles, exits, players))
	{
		ft_putendl_fd("Error\nInvalid map!\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	handle_player_position(char **map, int *player_x, int *player_y)
{
	player_position(map, player_x, player_y);
	if (!is_path_valid(map, *player_x, *player_y))
	{
		ft_putendl_fd("Error\nNo valid path!\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	so_long(t_game *game, char **map, int collectibles)
{
	game->mlx = mlx_init(680, 480, "so_long", true);
	if (!game->mlx)
		return (1);
	game->map = map;
	game->collectibles = collectibles;
	game->map_width = ft_strlen(game->map[0]);
	game->map_height = 0;
	while (game->map[game->map_height])
		game->map_height++;
	starting_position(game);
	game->move_counter = 0;
	load_images(game);
	render_map(game, game->map);
	mlx_key_hook(game->mlx, event_handler, game);
	mlx_loop(game->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int		collectibles;
	int		exits;
	int		players;
	char	**map;
	int		player_x;
	int		player_y;
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvalid number of arguments!\n", STDERR_FILENO);
		return (1);
	}
	if (validate_file_extension(argv[1]))
		return (1);
	map = read_map_into_array(argv[1]);
	if (handle_error(map))
		return (1);
	if (check_map(map, &collectibles, &exits, &players))
	{
		free_map(map);
		return (1);
	}
	if (handle_player_position(map, &player_x, &player_y))
	{
		free_map(map);
		return (1);
	}
	if (so_long(&game, map, collectibles))
	{
		free_map(game.map);
		return (1);
	}
	free_map(game.map);
	return (0);
}
