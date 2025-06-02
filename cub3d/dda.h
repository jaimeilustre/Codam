/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 09:15:39 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/02 09:28:06 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <math.h>

#include "colors.h"
#include "events.h"

#define PI 3.14159
#define PLAYER_SIZE 10
#define POINTER_SIZE 20
#define CELL_SIZE 30
#define CELLS_COUNT 20

#define WIDTH 720
#define HEIGHT 720

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

typedef struct	s_image {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_fvector {
	float	x;
	float	y;
}	t_fvector;

typedef struct	s_player {
	t_fvector	position;
	t_fvector	direction;
	t_fvector	plane;
	t_fvector	center;
	t_fvector	delta_position;
	float		rotation_angle;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_image		img;
	int			**map;
} t_data;

void cast_rays(t_game *game);

#endif