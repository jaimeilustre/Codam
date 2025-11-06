/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   life.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 11:00:49 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/06 12:03:41 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

// Initialize map with empty spaces
static void	init(t_game *game, char **argv)
{
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iterations = atoi(argv[3]);

	game->map = malloc(game->height * sizeof(char *));
	for (int y = 0; y < game->height; ++y)
	{
		game->map[y] = malloc(game->width * sizeof(char *));
		for (int x = 0; x < game->width; ++x)
			game->map[y][x] = ' ';
	}
}

// Fill map with starting pattern
static void fill(t_game *game)
{
	char buffer;
	int y = 0;
	int x = 0;
	bool	draw = false;

	// Controls
	while(read(STDIN_FILENO, &buffer, 1) == 1)
	{
		switch (buffer)
		{
			case ('w'):
				if (y > 0)
					--y;
				break ;
			case ('a'):
				if (x > 0)
					--x;
				break ;
			case ('s'):
				if (y < game->height - 1)
					++y;
				break ;
			case ('d'):
				if (x < game->width - 1)
					++x;
				break ;
			case ('x'):
				draw = !draw;
				break ;
			default:
				continue ;
		}
		// Mark cell as alive with 0 if draw is true and within map boundaries
		if (draw && y >= 0 && y < game->height && x >= 0 && x < game->width)
			game->map[y][x] = '0';
	}
	
}

// Count how many of the 8 neighbours are alive (0)
static int	count_neighbours(t_game game, int y, int x)
{
	int	count = 0;

	for (int dy = -1; dy < 2; ++dy)
	for (int dx = -1; dx < 2; ++dx)
	{
		// Skip if at origin
		if (dy == 0 && dx == 0)
			continue;
			
		// Calculate next cell to look at
		int ny = y + dy;
		int nx = x + dx;

		// If the cell is alive and within map boundaries, increase count
		if (ny >= 0 && ny < game.height && nx >= 0 && nx < game.width && game.map[ny][nx] == '0')
			count++;
	}
	return (count);
}

// Free old map
static void free_map(t_game *game)
{
	if (game->map)
	{
		for (int i = 0; i < game->height; i++)
		{
			if (game->map[i])
				free(game->map[i]);
		}
		free(game->map);
	}
}

static void	print_map(t_game game)
{
	for (int y = 0; y < game.height; ++y)
	{
		for (int x = 0; x < game.width; ++x)
			putchar(game.map[y][x]);
		putchar('\n');
	}
}

// Execute the game
static void execute(t_game *game)
{
	char **new_map = malloc(game->height * sizeof(char *));
	for (int y = 0; y < game->height; ++y)
		new_map[y] = malloc(game->width * sizeof(char *));

	for (int y = 0; y < game->height; ++y)
	for (int x = 0; x < game->width; ++x)
	{
		int neighbours = count_neighbours(*game, y, x);
		if (game->map[y][x] == '0')
		{
			if (neighbours == 2 || neighbours == 3)
				new_map[y][x] = '0';
			else
				new_map[y][x] = ' ';
		}
		else
		{
			if (neighbours == 3)
				new_map[y][x] = '0';
			else
				new_map[y][x] = ' ';
		}	
	}
	free_map(game);
	game->map = new_map;	
}

int main(int argc, char **argv)
{
	t_game	game;
	
	if (argc != 4)
		return (1);
	
	init(&game, argv);
	fill(&game);
	for (int i = 0; i < game.iterations; ++i)
		execute(&game);
	print_map(game);
	free_map(&game);
	return (0);
}