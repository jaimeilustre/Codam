/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fov.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:18:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/07 15:26:23 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

// Function to set a pixel using mlx_put_pixel
void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

typedef struct s_ray
{
	int		hit_x;    // where ray hit (map coordinate)
	int		hit_y;
	double	wall_x;  // exact intersection point in world coordinates
	double	distance;
	int		side;     // 0 = vertical wall (NS), 1 = horizontal (EW)
	t_line	line;  // line from player to hit point (for 2D drawing)
} t_ray;

// static t_ray ray_wall(t_vars *data, double angle)
// {
// 	t_ray ray;
// 	double ray_dir_x = cos(angle);
// 	double ray_dir_y = sin(angle);
// 	int map_x = (int)data->plx;
// 	int map_y = (int)data->ply;
// 	// Distance to next x or y side
// 	double side_dist_x;
// 	double side_dist_y;
// 	// Distance from one x-side to next x-side (grid spacing)
// 	double delta_dist_x = fabs(1 / ray_dir_x);
// 	double delta_dist_y = fabs(1 / ray_dir_y);
// 	int step_x;
// 	int step_y;
// 	int hit = 0;
// 	int side;
// 	// Setup step and initial sideDist
// 	if (ray_dir_x < 0)
// 	{
// 		step_x = -1;
// 		side_dist_x = (data->plx - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = (map_x + 1.0 - data->plx) * delta_dist_x;
// 	}

// 	if (ray_dir_y < 0)
// 	{
// 		step_y = -1;
// 		side_dist_y = (data->ply - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = (map_y + 1.0 - data->ply) * delta_dist_y;
// 	}
// 	// Perform DDA
// 	while (!hit)
// 	{
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_dist_x;
// 			map_x += step_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist_y += delta_dist_y;
// 			map_y += step_y;
// 			side = 1;
// 		}
// 		if (data->themap[map_y][map_x] == '1')
// 			hit = 1;
// 	}
// 	// Calculate exact wall hit position
// 	double perp_wall_dist;
// 	// if (side == 0)
// 	// 	perp_wall_dist = (side_dist_x - delta_dist_x);
// 	// else
// 	// 	perp_wall_dist = (side_dist_y - delta_dist_y);

// 	if (side == 0)
//    		perp_wall_dist = (map_x - data->plx + (1 - step_x) / 2.0) / ray_dir_x;
// 	else
//     	perp_wall_dist = (map_y - data->ply + (1 - step_y) / 2.0) / ray_dir_y;
	
// 	double hit_x = data->plx + ray_dir_x * perp_wall_dist;
// 	double hit_y = data->ply + ray_dir_y * perp_wall_dist;

// 	ray.hit_x = map_x;
// 	ray.hit_y = map_y;
// 	ray.wall_x = hit_x;
// 	ray.distance = perp_wall_dist;
// 	ray.side = side;
// 	ray.line.x1 = (int)(data->plx * 32);
// 	ray.line.y1 = (int)(data->ply * 32);
// 	ray.line.x2 = (int)(hit_x * 32);
// 	ray.line.y2 = (int)(hit_y * 32);
// 	return ray;
// }

static t_ray ray_wall(t_vars *data, double angle)
{
    t_ray ray;
    double ray_dir_x = cos(angle);
    double ray_dir_y = sin(angle);

    int map_x = (int)data->plx;
    int map_y = (int)data->ply;

    double delta_dist_x = fabs(1.0 / ray_dir_x);
    double delta_dist_y = fabs(1.0 / ray_dir_y);
    double side_dist_x, side_dist_y;

    int step_x = (ray_dir_x < 0) ? -1 : 1;
    int step_y = (ray_dir_y < 0) ? -1 : 1;

    if (ray_dir_x < 0)
        side_dist_x = (data->plx - map_x) * delta_dist_x;
    else
        side_dist_x = (map_x + 1.0 - data->plx) * delta_dist_x;

    if (ray_dir_y < 0)
        side_dist_y = (data->ply - map_y) * delta_dist_y;
    else
        side_dist_y = (map_y + 1.0 - data->ply) * delta_dist_y;

    int hit = 0, side;
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x      += step_x;
            side        = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y      += step_y;
            side        = 1;
        }
        if (data->themap[map_y][map_x] == '1')
            hit = 1;
    }

    // PERPENDICULAR DISTANCE to the wall:
    double perp_wall_dist;
    if (side == 0)
        perp_wall_dist = (map_x - data->plx + (1 - step_x) / 2.0) / ray_dir_x;
    else
        perp_wall_dist = (map_y - data->ply + (1 - step_y) / 2.0) / ray_dir_y;

    ray.hit_x   = map_x;
    ray.hit_y   = map_y;
    ray.distance= perp_wall_dist;
    ray.side    = side;
    ray.line.x1 = (int)(data->plx * 32);
    ray.line.y1 = (int)(data->ply * 32);
    ray.line.x2 = (int)((data->plx + ray_dir_x * perp_wall_dist) * 32);
    ray.line.y2 = (int)((data->ply + ray_dir_y * perp_wall_dist) * 32);

    return ray;
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

void draw_fov_line(t_vars *data)
{
	const int num_rays = 60;
	const double fov = PI / 3;
	const double start_angle = data->pla - fov / 2;
	const double step = fov / num_rays;

	clear_image(data->fovlines);

	for (int i = 0; i <= num_rays; i++)
	{
		double angle = start_angle + i * step;
		t_ray ray = ray_wall(data, angle);
		bresenham_line(data->fovlines, ray.line, 0xFFFFFF);
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

// void draw_3d_view(t_vars *data)
// {
//     int screen_w = data->view3d->width;
//     int screen_h = data->view3d->height;
//     int num_rays = 60;
//     double fov     = PI / 3.0;
//     double start_a = data->pla - fov / 2.0;
//     double step    = fov / (double)num_rays;

//     // distance from camera to projection plane
//     double proj_plane = (screen_w / 2.0) / tan(fov / 2.0);

//     clear_image(data->view3d);

//     for (int ray_i = 0; ray_i < num_rays; ray_i++)
//     {
//         double angle   = normalize_angle(start_a + ray_i * step);
//         t_ray  info    = ray_wall(data, angle);
//         double dist    = info.distance;
//         if (dist < 0.01) dist = 0.01;

		
// 		// DEBUG:
// 		if (ray_i % 5 == 0)   // print every 5th ray
//    			printf("ray %2d — perp_dist=%.2f\n", ray_i, dist);
		
// 		double world_tile = 1.0;
//     	int wall_h = (int)((world_tile * proj_plane) / dist);

//         // classic Wolf–3D projection
//         // int wall_h = (int)((32.0 * proj_plane) / dist);

//         int top    = (screen_h / 2) - (wall_h / 2);
//         int bottom = top + wall_h;
//         if (top    < 0)         top    = 0;
//         if (bottom > screen_h)  bottom = screen_h;

//         int x_start = (ray_i * screen_w) / num_rays;
//         int strip_w = screen_w / num_rays;

//         uint32_t ceil_col = 0xFF00FF;
//         uint32_t floor_col= 0x00FFFF;
//         uint32_t wall_col = (info.side == 1) ? 0x888888 : 0xAAAAAA;

//         // Optional debug:
//         // if (ray_i % 10 == 0)
//         //     printf("ray %d: dist=%.2f, wall_h=%d\n",
//         //            ray_i, dist, wall_h);

//         for (int dx = 0; dx < strip_w; dx++)
//         {
//             int px = x_start + dx;
//             for (int y = 0; y < top;    y++) set_pixel(data->view3d, px, y, ceil_col);
//             for (int y = top; y < bottom; y++) set_pixel(data->view3d, px, y, wall_col);
//             for (int y = bottom; y < screen_h; y++) set_pixel(data->view3d, px, y, floor_col);
//         }
//     }
// }

void draw_3d_view(t_vars *data)
{
    int  screen_w   = data->view3d->width;
    int  screen_h   = data->view3d->height;
    // int  num_rays   = 60;
    double fov      = PI/3.0;
    double start_a  = data->pla - fov/2.0;
    double proj_plane = (screen_w/2.0) / tan(fov/2.0);

    clear_image(data->view3d);

    for (int px = 0; px < screen_w; px++)
    {
        // map this screen‐column to a ray index in [0,num_rays)
        double ray_frac = (double)px / (double)screen_w;
        double angle    = normalize_angle(start_a + ray_frac * fov);
        t_ray info      = ray_wall(data, angle);

        double dist = info.distance;
        if (dist < 0.01) dist = 0.01;

        int wall_h = (int)((1.0 * proj_plane) / dist);
        if (wall_h > screen_h) wall_h = screen_h;

        int top    = (screen_h/2) - (wall_h/2);
        int bottom = top + wall_h;
        if (top < 0)      top = 0;
        if (bottom > screen_h) bottom = screen_h;

        uint32_t ceil_col = 0xFF00FF;
        uint32_t wall_col = (info.side ? 0x888888 : 0xAAAAAA);
        uint32_t floor_col= 0x00FFFF;

        // draw this single‐px slice
        for (int y = 0; y < top;    y++) set_pixel(data->view3d, px, y, ceil_col);
        for (int y = top; y < bottom; y++) set_pixel(data->view3d, px, y, wall_col);
        for (int y = bottom; y < screen_h; y++) set_pixel(data->view3d, px, y, floor_col);
    }
}



