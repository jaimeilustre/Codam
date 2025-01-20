/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 16:31:20 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/20 13:49:15 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <MLX42/MLX42.h>
# include "libft/libft.h"
# include "get_next_line.h"

typedef struct	s_game
{
	mlx_t		*mlx;
	mlx_image_t	*wall_img;
	mlx_image_t	*player_img;
	mlx_image_t	*floor_img;
	mlx_image_t	*collectible_img;
	mlx_image_t	*exit_img;
	char		**map;
	int			map_width;
	int			map_height;
	int			position_y;
	int			position_x;
	int			move_counter;
	int			collectibles;
}				t_game;

// Map parsing
int		count_lines(const char *file);
char	**read_map_into_array(const char *file);

// Map validation
bool	check_walls(char **map);
bool	check_elements(char **map, int *collectibles, int *exits, int *players);

// Check valid path
char	**copy_map(char **map);
void	flood_fill(char **map, int x, int y);
bool	is_path_valid(char **map, int player_x, int player_y);
void	player_position(char **map, int *player_x, int *player_y);

// Graphics rendering
void	load_images(t_game *game);
void	render_map(t_game *game, char **map);

#endif