/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_rendering.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 11:03:04 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/22 17:14:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"

void	load_image(t_game *game, const char *path, mlx_image_t **img)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		exit(EXIT_FAILURE);
	*img = mlx_texture_to_image(game->mlx, texture);
	if (!*img)
	{
		mlx_delete_texture(texture);
		exit(EXIT_FAILURE);
	}
	mlx_resize_image(*img, 64, 64);
	mlx_delete_texture(texture);
}

void	load_images(t_game *game)
{
	load_image(game, "textures/wall.png", &game->wall_img);
	load_image(game, "textures/player.png", &game->player_img);
	load_image(game, "textures/floor.png", &game->floor_img);
	load_image(game, "textures/collectible.png", &game->collectible_img);
	load_image(game, "textures/exit.png", &game->exit_img);
}

void	free_images(t_game *game)
{
	if (game->wall_img)
		mlx_delete_image(game->mlx, game->wall_img);
	if (game->player_img)
		mlx_delete_image(game->mlx, game->player_img);
	if (game->floor_img)
		mlx_delete_image(game->mlx, game->floor_img);
	if (game->collectible_img)
		mlx_delete_image(game->mlx, game->collectible_img);
	if (game->exit_img)
		mlx_delete_image(game->mlx, game->exit_img);
	
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
			if (map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall_img, x * 64, y * 64);
			else if (map[y][x] == 'C')
				mlx_image_to_window(game->mlx,
					game->collectible_img, x * 64, y * 64);
			else if (map[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->exit_img, x * 64, y * 64);
			else if (map[y][x] == 'P')
				mlx_image_to_window(game->mlx,
					game->player_img, x * 64, y * 64);
			x++;
		}
		y++;
	}
}
