/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 17:11:09 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/20 17:59:48 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <MLX42/MLX42.h>
#include "so_long.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\n");
		return (1);
	}
	char **map = read_map_into_array(argv[1]);
	if (!map)
	{
		printf("Error\n");
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
	game.collectibles = collectibles;
	game.map_width = ft_strlen(game.map[0]);
	game.map_height = 0;
	while (game.map[game.map_height])
		game.map_height++;
	
	starting_position(&game);
	game.move_counter = 0;
	load_images(&game);
	render_map(&game, game.map);
	mlx_key_hook(game.mlx, event_handler, &game);
	mlx_loop(game.mlx);
	for (int i = 0; game.map[i]; i++)
		free(game.map[i]);
	free(game.map);
	return (0);
}
