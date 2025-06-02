/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 09:23:48 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/02 09:35:34 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void cast_rays(t_data *game)
{
	int x;
	int y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		/*1. Calculate ray position and direction*/
		float camera_x = 2 * x / (float)SCREEN_WIDTH - 1;
		float ray_dir_x = game->player.direction.x + game->player.plane.x * camera_x;
		float ray_dir_y = game->player.direction.y + game->player.plane.y * camera_x;

		/*2. Map position*/
		int map_x = (int)game->player.position.x;
		int map_y = (int)game->player.position.y;

		/*3. Length of ray from one x or y-side to next x or y-side*/
		float delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabsf(1 / ray_dir_x);
		float delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabsf(1 / ray_dir_y);

		float side_dist_x, side_dist_y;

		/*4. Direction to step and initial side_dist*/
		int step_x, step_y;
		int hit = 0;
		int side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player.position.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player.position.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player.position.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player.position.y) * delta_dist_y;
		}

		/*5. Perform DDA*/
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->map[map_y][map_x] > 0)
				hit = 1;
		}
		
		/*6. Calculate distance to wall*/
		float perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - game->player.position.x + (1 - step_x) / 2.0f) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player.position.y + (1 - step_y) / 2.0f) / ray_dir_y;

		/*7. Calculate line height and draw range*/
		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

		/*8. Choose color*/
		int color = 0x00FF0000; // red
		if (side == 1)
			color = 0x00880000; // darker red

		/*9. Draw vertical line*/
		y = draw_start;
		while (y <= draw_end)
		{
			my_mlx_pixel_put(game, x, y, color);
			y++;
		}
		x++;
	}
}

