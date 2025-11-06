/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bsq.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 13:41:30 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/06 15:44:21 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// Reads symbols and line count
static int	parse_header(t_map *map, FILE *file)
{
	if (fscanf(file, "%d %c %c %c\n",
			&map->rows, &map->e, &map->o, &map->f) != 4)
		return (0);
	if (map->e == map->o || map->e == map->f
			|| map->o == map->f || map->rows <= 0)
		return (0);
	map->map = calloc(map->rows, sizeof(char *));
	return !!map->map;
}

// Reads map lines and validates them
static int read_map(t_map *map, FILE *file)
{
	size_t len = 0;
	ssize_t	r = 0;
	
	for (int i = 0; i < map->rows; i++)
	{
		r = getline(&map->map[i], &len, file);
		if (r <= 0 || (i && r != (ssize_t)(map->cols + 1)))
			return (0);
		if (!i)
			map->cols = r - 1;
		for (int j = 0; j < map->cols; j++)
		{
			if (map->map[i][j] != map->e && map->map[i][j] != map->o)
				return (0);
		}
	}
	return (1);
}

// Finds and fills bigest square
static void solve(t_map *m)
{
	int **dp = calloc(m->rows, sizeof(int *));
	int max = 0;
	int x = 0;
	int y = 0;
	
	for (int i = 0; i < m->rows; i++)
		dp[i] = calloc(m->cols, sizeof(int));
	
	for (int i = 0; i < m->rows; i++)
	for (int j = 0; j < m->cols; j++)
	{
		if (m->map[i][j] == m->e)
		{
			if (i && j)
			{
				int a = dp[i - 1][j];
				int b = dp[i][j - 1];
				int c = dp[i - 1][j - 1];
				
				dp[i][j] = 1 + (a < b ? (a < c ? a : c) : (b < c ? b : c));
			}
			else
				dp[i][j] = 1;
	
			if (dp[i][j] > max)
			{
				max = dp[i][j];
				y = i;
				x = j;
			}
		}
	}
	for (int i = y; i > y - max; i--)
		for (int j = x; j > x - max; j--)
			m->map[i][j] = m->f;
	
	for (int i = 0; i < m->rows; i++)
		fputs(m->map[i], stdout);
	for (int i = 0; i < m->rows; i++)
	{
		free(m->map[i]);
		free(dp[i]);
	}
	free(m->map);
	free(dp);
}

// Opens file and calls all the helper functions
static void	process(const char *path)
{
	FILE *f = path ? fopen(path, "r") : stdin;
	if (!f)
	{
		fprintf(stderr, "map error\n");
		return ;
	}
	t_map m = {0};
	if (!parse_header(&m, f) || !read_map(&m, f))
		fprintf(stderr, "map error\n");
	else
		solve(&m);
	if (path)
		fclose(f);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		process(NULL);
	for (int i = 1; i < argc; i++)
	{
		process(argv[i]);
		if (i < argc - 1)
			putchar('\n');
	}
	return (0);
}

