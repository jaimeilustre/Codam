/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 16:31:20 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/01/21 16:16:55 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <MLX42/MLX42.h>
# include "libft/libft.h"

typedef struct s_map_info
{
	char	**map;
	int		width;
	int		height;
}				t_map_info;

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
	int			position_y;
	int			position_x;
	int			move_counter;
	int			collectibles;
}				t_game;

// Map parsing
int		count_lines(const char *file);
char	**read_lines_from_file(int fd, int lines);
char	**read_map_into_array(const char *file);

// Map validation
bool	check_walls(char **map);
bool	check_elements(char **map, int *collectibles, int *exits, int *players);

// Check valid path
void	flood_fill(char **map, int x, int y);
bool	check_collectibles(char **map, char **map_copy);
bool	check_exit(char **map, char **map_copy);
void	modify_collectibles(char **map, char **map_copy);
bool	is_path_valid(char **map, int player_x, int player_y);

// Graphics rendering
void	load_image(t_game *game, const char *path, mlx_image_t **img);
void	load_images(t_game *game);
void	render_map(t_game *game, char **map);

// Player movement
bool	allowed_movements(t_map_info *map_info, int x, int y);
void	handle_collectible(t_game *game, int new_x, int new_y);
void	handle_exit(t_game *game);
void	move_player(t_game *game, int dx, int dy, char **map);
void	event_handler(mlx_key_data_t keydata, void *param);

// Main game
int		handle_error(char **map);
int		check_map(char **map, int *collectibles, int *exits, int *players);
int		handle_player_position(char **map, int *player_x, int *player_y);
int		so_long(t_game *game, char **map, int collectibles);
int		main(int argc, char **argv);

// Utils
char	**copy_map(char **map);
void	free_map(char **map);
void	player_position(char **map, int *player_x, int *player_y);
void	starting_position(t_game *game);
int		validate_file_extension(const char *filename);

#endif