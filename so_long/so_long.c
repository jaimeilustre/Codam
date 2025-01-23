/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 17:11:09 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/23 16:09:32 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <MLX42/MLX42.h>
#include "so_long.h"

int	map_allocation(char **map)
{
	if (!map)
	{
		ft_putendl_fd("Error\nNo/empty file!", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	map_elements(char **map, t_game *game)
{
	if (!check_walls(map) || !check_elements(map, &game->collectibles,
			&game->exits, &game->players))
	{
		ft_putendl_fd("Error\nInvalid map!", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	valid_path(char **map, t_game *game)
{
	player_position(map, &game->position_x, &game->position_y);
	if (!is_path_valid(map, game->position_x, game->position_y))
	{
		ft_putendl_fd("Error\nNo valid path!", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	window_size(char **map, int *window_width, int *window_height)
{
	*window_width = ft_strlen(map[0]) * 64;
	*window_height = 0;
	while (map[*window_height])
		(*window_height)++;
	*window_height *= 64;
}

int	so_long(t_game *game, char **map, int collectibles)
{
	int	window_width;
	int	window_height;

	window_size(map, &window_width, &window_height);
	game->mlx = mlx_init(window_width, window_height, "so_long", true);
	if (!game->mlx)
	{
		free_map(game->map);
		exit(EXIT_FAILURE);
	}
	game->map = map;
	game->collectibles = collectibles;
	game->map_width = ft_strlen(game->map[0]);
	game->map_height = window_height / 64;
	starting_position(game);
	game->move_counter = 0;
	load_images(game);
	render_map(game, game->map);
	mlx_key_hook(game->mlx, event_handler, game);
	mlx_loop(game->mlx);
	free_images(game);
	mlx_terminate(game->mlx);
	free_map(game->map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	**map;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvalid number of arguments!", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (file_extension(argv[1]))
		exit(EXIT_FAILURE);
	map = read_map_into_array(argv[1]);
	if (map_allocation(map))
	{
		free_map(map);
		exit(EXIT_FAILURE);
	}
	if (map_elements(map, &game))
	{
		free_map(map);
		exit(EXIT_FAILURE);
	}
	if (valid_path(map, &game))
	{
		free_map(map);
		exit(EXIT_FAILURE);
	}
	if (so_long(&game, map, game.collectibles))
	{
		free_map(game.map);
		exit(EXIT_FAILURE);
	}
	return (0);
}
