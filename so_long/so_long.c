/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 17:11:09 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/24 11:10:51 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <MLX42/MLX42.h>
#include "so_long.h"

void	file_extension(const char *filename)
{
	const char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".ber", 4) != 0
		|| ft_strlen(extension) != 4)
	{
		ft_putendl_fd("Error\nInvalid file extension!", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	map_allocation(char **map)
{
	if (!map)
	{
		ft_putendl_fd("Error\nNo/empty file!", STDERR_FILENO);
		free_map(map);
		exit(EXIT_FAILURE);
	}
}

void	validate_map(t_game *game, char **map)
{
	if (!check_walls(map) || !check_elements(map, &game->collectibles,
			&game->exits, &game->players))
	{
		ft_putendl_fd("Error\nInvalid map!", STDERR_FILENO);
		free_map(map);
		exit(EXIT_FAILURE);
	}
	game->map = map;
	player_position(game);
	if (!valid_path(map, game->position_x, game->position_y))
	{
		ft_putendl_fd("Error\nNo valid path!", STDERR_FILENO);
		free_map(map);
		exit(EXIT_FAILURE);
	}
}

int	so_long(t_game *game, char **map)
{
	window_size(game, map);
	game->mlx = mlx_init(game->window_width,
			game->window_height, "so_long", true);
	if (!game->mlx)
	{
		free_map(game->map);
		exit(EXIT_FAILURE);
	}
	game->map = map;
	game->map_width = ft_strlen(game->map[0]);
	game->map_height = game->window_height / 64;
	player_position(game);
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
	file_extension(argv[1]);
	map = read_map_into_array(argv[1]);
	map_allocation(map);
	validate_map(&game, map);
	so_long(&game, map);
	return (0);
}
