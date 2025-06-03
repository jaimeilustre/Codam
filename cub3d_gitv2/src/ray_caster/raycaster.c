/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 10:02:34 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/03 11:39:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void draw_rays(t_vars *vars)
{
	int		r; // number of rays (60 in this case for 60 degree field of view)
	float	ra; // ray angle
	float	rx; // the intersection point where the ray hits something in the x axis
	float	ry; // the intersection point where the ray hits something in the y axis
	float	ra_rad; // ray angle in radians
	float	Tan; // tangent of the ray angle used for calculating horizontal or vertical interestions
	float	disH; // distance from player to the horizontal wall hit
	float	disV; // distance from player to the vertical wall hit
	float	vx; // final vertical wall hit x coordinates (where the vertical ray hit the wall)
	float	vy; // final vertical wall hit y coordinates (where the vertical ray hit the wall)
	float	px; // player's current x position on the map
	float	py; // player's current y position on the map

	ra = vars->pl_angle + 30; // Starting ray angle
	r = 0;
	while (r < 60)
	{
		int	dof; // depth of field; how the ray travels through the grid before hitting a wall
		int	mx; // map grid index the ray is currently checking x
		int	my; // map grid index the ray is currently checking y
		int	mp; // map position index (1D array index)
		float xo; // ray_step offsets in x direction
		float yo; // ray_step offsets in y direction

		/*HORIZONTAL CALCULATIONS*/
		dof = 0;
		Tan = 1.0 / Tan;
		if (sin (ra_rad) > 0.001) // Looking up
		{
			ry = ((int)py / 64) * 64 - 0.0001;
			rx = (py - ry) * Tan + px;
			yo = -64;
			xo = -yo * Tan;
		}
		else if (sin(ra_rad) < -0.001) // Looking down
		{
			ry = ((int)py / 64) * 64 + 64;
			rx = (py -ry) * Tan + px;
			yo = 64;
			xo = -yo * Tan;
		}
		else // Looking left or right with no hit
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * 10 + mx;
			if (vars->themap[my] && vars->themap[my][mx] == '1')
			{
				dof = 8;
				disH = cos(ra_rad) * (rx - px) - sin(ra_rad) * (ry - py);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		
		/*VERTICAL CALCULATIONS*/
		ra = fmod(ra, 360.0f);
		if (ra < 0)
			ra += 360.0f;
		ra_rad = degree_to_radians(ra);
		Tan = tan(ra_rad);
		dof = 0;
		disV = 1e6;
		/*Finds the first grid interesections and the offsets to step ray along the grid */
		if (cos(ra_rad) > 0.001) // Looking up
		{
			rx = ((int)px / 64) * 64 + 64;
			ry = (px -rx) * Tan + py;
			xo = 64;
			yo = -xo * Tan;
		}
		else if (cos(ra_rad) < -0.001) // Looking down
		{
			rx = ((int)px / 64) * 64 - 0.001;
			ry = (px - rx) * Tan + py;
			xo = -64;
			yo = -xo * Tan;
		}
		else // Looking left or right with no hit
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		/*Steps along the grid using xo and yo until a wall ('1') is found*/
		while (dof < 8)
		{
			mx = (int)rx / 64;
			my = (int)ry / 64;
			mp = my * 10 + mx; // adjust 10 to map width
			if (vars->themap[my] && vars->themap[my][mx] == '1')
			{
				dof = 8;
				vx = rx;
				vy = ry;
				disV = cos(ra_rad) * (rx - px) - sin(ra_rad) * (ry - py);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		
		/*DETERMINE NEAREST HIT POINT (HORIZONTAL OR VERTICAL)*/
		float disFINAL;
		float fx;
		float fy;
		
		disFINAL = disH;
		fx = rx;
		fy = ry;
		if (disV < disH)
		{
			disFINAL = disV;
			fx = vx;
			fy = vy;
		}
		
		r++;
	}
	
}
