/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 11:03:04 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/20 08:40:05 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <MLX42/MLX42.h>
#include "so_long.h"

void	load_images(t_game *game)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("textures/wall.png");
	if (!texture)
	{
		fprintf(stderr, "Error: Failed to load wall texture.\n");
		exit (1);
	}
	game->wall_img = mlx_texture_to_image(game->mlx, (mlx_texture_t *)texture);
	mlx_resize_image(game->wall_img, 64, 64);
	mlx_delete_texture(texture);
	texture = mlx_load_png("textures/player.png");
	if (!texture)
	{
		fprintf(stderr, "Error: Failed to load player texture.\n");
		exit(1);
	}
	game->player_img = mlx_texture_to_image(game->mlx, (mlx_texture_t *)texture);
	mlx_resize_image(game->player_img, 64, 64);
	mlx_delete_texture(texture);
	texture = mlx_load_png("textures/floor.png");
	if (!texture)
	{
		fprintf(stderr, "Error: Failed to load floor texture.\n");
		exit(1);
	}
	game->floor_img = mlx_texture_to_image(game->mlx, (mlx_texture_t *)texture);
	mlx_resize_image(game->floor_img, 64, 64);
	mlx_delete_texture(texture);
	texture = mlx_load_png("textures/collectible.png");
	if (!texture)
	{
		fprintf(stderr, "Error: Failed to load collectible texture.\n");
		exit(1);
	}
	game->collectible_img = mlx_texture_to_image(game->mlx, (mlx_texture_t *)texture);
	mlx_resize_image(game->collectible_img, 64, 64);
	mlx_delete_texture(texture);
	texture = mlx_load_png("textures/exit.png");
	if (!texture)
	{
		fprintf(stderr, "Error: Failed to load exit texture.\n");
		exit(1);
	}
	game->exit_img = mlx_texture_to_image(game->mlx, (mlx_texture_t *)texture);
	mlx_resize_image(game->exit_img, 64, 64);
	mlx_delete_texture(texture);
}

void	render_map(t_game *game, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			mlx_image_to_window(game->mlx, game->floor_img, x * 64, y * 64);
			// mlx_set_instance_depth(&game->floor_img->instances[0], 0);
			if (map[y][x] == '1')
			{
				mlx_image_to_window(game->mlx, game->wall_img, x * 64, y * 64);
				// mlx_set_instance_depth(&game->wall_img->instances[0], 1);
			}
			else if (map[y][x] == 'C')
			{
				mlx_image_to_window(game->mlx, game->collectible_img, x * 64, y * 64);
				// mlx_set_instance_depth(&game->collectible_img->instances[0], 2);
			}
			else if (map[y][x] == 'E')
			{
				mlx_image_to_window(game->mlx, game->exit_img, x * 64, y * 64);
				// mlx_set_instance_depth(&game->exit_img->instances[0], 2);
			}
			else if (map[y][x] == 'P')
			{
				mlx_image_to_window(game->mlx, game->player_img, x * 64, y * 64);
				// mlx_set_instance_depth(&game->player_img->instances[0], 3);
			}
			x++;
		}
		y++;
	}
}

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s <map.ber>\n", argv[0]);
// 		return (1);
// 	}
// 	char **map = read_map_into_array(argv[1]);
// 	if (!map)
// 	{
// 		fprintf(stderr, "Error: Failed to read map.\n");
// 		return (1);
// 	}
// 	int	collectibles, exits, players;
// 	if (!check_walls(map) || !check_elements(map, &collectibles, &exits, &players))
// 	{
// 		fprintf(stderr, "Error: Invalid map.\n");
// 		for (int i = 0; map[i]; i++)
// 			free(map[i]);
// 		free(map);
// 		return (1);
// 	}
// 	int	player_x, player_y;
// 	find_player(map, &player_x, &player_y);
// 	if (!is_path_valid(map, player_x, player_y))
// 	{
// 		fprintf(stderr, "Error: no valid path exists");
// 		for (int i = 0; map[i]; i++)
// 			free(map[i]);
// 		free(map);
// 		return (1);
// 	}
// 	printf("Map is valid! Collectibles: %d, Exits: %d, Players: %d\n", collectibles, exits, players);

// 	t_game	game;
// 	game.mlx = mlx_init(680, 480, "so_long", true);
// 	if (!game.mlx)
// 	{
// 		fprintf(stderr, "Error: failed to initialize MiniLibx.\n");
// 		return (1);
// 	}
// 	load_images(&game);
// 	render_map(&game, map);
// 	mlx_loop(game.mlx);
// 	for (int i = 0; map[i]; i++)
// 		free(map[i]);
// 	free(map);
// 	return (0);
// }
