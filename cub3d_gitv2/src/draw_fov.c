/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fov.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:18:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/03 14:38:20 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

// Function to set a pixel using mlx_put_pixel
static void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

static t_line ray_wall(t_vars *data, double angle)
{
	t_line	line;
	double	ray_x = data->plx;
	double	ray_y = data->ply;
	double	dx = cos(angle);
	double	dy = sin(angle);
	double	step = 0.05; // fine enough step for smooth lines
	int		map_x; 
	int		map_y;

	line.x1 = (int)(data->plx * 32);
	line.y1 = (int)(data->ply * 32);

	while (1)
	{
		ray_x += dx * step;
		ray_y += dy * step;
		map_x = (int)(ray_x);
		map_y = (int)(ray_y);
		if (data->themap[map_y][map_x] == '1') // hit wall
			break;
	}
	line.x2 = (int)(ray_x * 32);
	line.y2 = (int)(ray_y * 32);
	return (line);
}

// Function to draw a line using Bresenham's algorithm
void bresenham_line(mlx_image_t *img, t_line line, uint32_t color)
{
	int dx = abs(line.x2 - line.x1);
	int dy = abs(line.y2 - line.y1);

	int sx; // new;
	int sy;

	int e2;
	int err;

	//direction.
	if (line.x1 < line.x2)
		sx = 1;
	else
		sx = -1;

	if (line.y1 < line.y2)
		sy = 1;
	else
		sy = -1;

	err = dx - dy;
	while (1) {
		set_pixel(img, line.x1, line.y1, color);
		if (line.x1 == line.x2 && line.y1 == line.y2) // Reached endpoint
			break;

		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			line.x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			line.y1 += sy;
		}
	}
}

void	clear_image(mlx_image_t *img)
{
	uint32_t i = 0;
	while (i < img->width * img->height)
	{
		// Each pixel = 4 bytes (RGBA)
		img->pixels[i * 4 + 0] = 0; // R
		img->pixels[i * 4 + 1] = 0; // G
		img->pixels[i * 4 + 2] = 0; // B
		img->pixels[i * 4 + 3] = 0; // A
		i++;
	}
}

void	draw_fov_line(t_vars *data)
{
	const int num_rays = 700;  // number of rays
	const double fov = PI / 3;  // 60 degrees field of view
	const double start_angle = data->pla - fov / 2;
	const double step = fov / num_rays;
	int	i = 0;
	t_line line;

	clear_image(data->fovlines);
	while (i <= num_rays)
	{
		double angle = start_angle + i * step;
		line = ray_wall(data, angle);
		bresenham_line(data->fovlines, line, 0xFFFFFF);
		i++;
	}
}

double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

void	draw_3d_view(t_vars *data)
{
	// int	screen_w = 700;
	int	screen_h = 400;
	int	tile_size = 32;
	int	num_rays = 60;
	double	fov = PI / 3;
	double	start_angle = data->pla - fov / 2;
	double	step = fov/num_rays;

	clear_image(data->view3d);
	
	int	ray = 0;
	while (ray <= num_rays)
	{
		double	angle = normalize_angle(start_angle + ray * step);
		t_line	rayline = ray_wall(data, angle);

		/*Calculate distance from player to wall*/
		double	ray_x = rayline.x2 / 32.0;
		double	ray_y = rayline.y2 / 32.0;
		double	dx = ray_x - data->plx;
		double	dy = ray_y - data->ply;
		double	distance = sqrt(dx * dx + dy * dy);

		/*Fisheye correction*/
		distance *= cos(angle - data->pla);
		if (distance < 0.01)
			distance = 0.01;
		
		/*Calculate wall height based on distance*/
		int	wall_height = (int)((tile_size * screen_h) / distance);
		if (wall_height > screen_h)
			wall_height = screen_h;

		printf("Ray %d angle %.2f distance %.2f wall_height %d\n", ray, angle, distance, wall_height);

		int top = (screen_h / 2) - (wall_height / 2);
		int	bottom = top + wall_height;

		/*Draw ceiling*/
		int y = 0;
		while (y < top)
		{
			set_pixel(data->view3d, ray, y, 0x333366);
			y++;
		}
		
		/*Draw wall slice*/
		y = top;
		while (y < bottom)
		{
			// int color = 0x010101 * ray;
			set_pixel(data->view3d, ray, y, 0xAAAAAA);
			// set_pixel(data->view3d, ray, y, color);
			y++;
		}

		/*Draw floor*/
		y = bottom;
		while (y < screen_h)
		{
			set_pixel(data->view3d, ray, y, 0x333300);
			y++;
		}
		
		ray++;
	}
}
