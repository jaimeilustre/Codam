/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 16:31:20 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/27 17:32:21 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include "libft/libft.h"

typedef struct s_game
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
	int			window_width;
	int			window_height;
	int			position_y;
	int			position_x;
	int			move_counter;
	int			collectibles;
	int			exits;
	int			players;
}				t_game;

// Map parsing
int		count_lines(const char *file);
char	**read_lines_from_file(int fd, int lines);
char	**read_map_into_array(const char *file);
void	free_map(char **map);
char	**copy_map(char **map);

// Map validation
bool	check_walls(char **map);
bool	check_elements(char **map, int *collectibles, int *exits, int *players);

// Check valid path
void	flood_fill(char **map, int x, int y);
bool	check_collectibles(char **map, char **map_copy);
bool	check_exit(char **map, char **map_copy);
void	modify_collectibles(char **map, char **map_copy);
bool	valid_path(char **map, int position_x, int position_y);

// Graphics rendering
void	load_image(t_game *game, const char *path, mlx_image_t **img);
void	load_images(t_game *game);
void	free_images(t_game *game);
void	render_map(t_game *game, char **map);

// Player movement
bool	allowed_movements(t_game *game, int x, int y);
void	handle_collectible(t_game *game, int new_x, int new_y);
void	handle_exit(t_game *game);
void	move_player(t_game *game, int dx, int dy, char **map);
void	event_handler(mlx_key_data_t keydata, void *param);

// Main game
void	file_extension(const char *filename);
void	map_allocation(char **map);
void	validate_map(t_game *game, char **map);
int		so_long(t_game *game, char **map);
int		main(int argc, char **argv);

// Utils
void	player_position(t_game *game);
void	window_size(t_game *game, char **map);

#endif