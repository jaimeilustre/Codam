/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bsq.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 13:41:30 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/09 12:31:18 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// Reads and validates the first line
static int	parse_header(t_map *m, FILE *f)
{
	// checks if they are all there
	if (fscanf(f, "%d %c %c %c\n",
			&m->rows, &m->e, &m->o, &m->f) != 4)
		return (0);
	// checks if their unique and at least one row
	if (m->e == m->o || m->e == m->f
			|| m->o == m->f || m->rows <= 0)
		return (0);
	m->map = calloc(m->rows, sizeof(char *));
	return !(!m->map);
}

// Reads each map line with getline
static int read_map(t_map *m, FILE *f)
{
	size_t len = 0;
	size_t	r = 0;

	for (int i = 0; i < m->rows; i++)
	{
		r = getline(&m->map[i], &len, f);
		// Checks if lines are the same length as cols
		if (r <= 0 || (i && r != (size_t)(m->cols + 1)))
			return (0);
		// first line determines the map with (-1 to ignore \n)
		if (!i)
			m->cols = r - 1;
		for (int j = 0; j < m->cols; j++)
		{
			// Checks if each character is empty or obstacle
			if (m->map[i][j] != m->e && m->map[i][j] != m->o)
				return (0);
		}
	}
	return (1);
}

// Finds and fills bigest square
static void solve(t_map *m)
{
	// Step 1: allocate a dynamic programming table by creating a 2d array of the same size as the map
	int **dp = calloc(m->rows, sizeof(int *));	
	for (int i = 0; i < m->rows; i++)
		dp[i] = calloc(m->cols, sizeof(int));

	// Step 2: initialize helper variables
	int max = 0; // largest square size found
	int x = 0; // x-coordinate (column) of bottom right corner
	int y = 0; // y-coordinate (row) of bottom right corner
	
	// Step 3: scan the map and fill the 2d array
	for (int i = 0; i < m->rows; i++)
	for (int j = 0; j < m->cols; j++)
	{
		if (m->map[i][j] == m->e)
		{
			if (i && j)
			{
				// For each cell that is empty, we check the 3 neighbouring squares
				int a = dp[i - 1][j]; // Top
				int b = dp[i][j - 1]; // Left
				int c = dp[i - 1][j - 1]; // Top left diagonal
				
				// Largest square is 1 bigger than the smallest square neighbouring it
				dp[i][j] = 1 + (a < b ? (a < c ? a : c) : (b < c ? b : c));
			}
			else
				// If we're at the top row or left column, there are no cells above it
				dp[i][j] = 1;
	
			// Every time we find the biggest square, we update its size and coordinates
			if (dp[i][j] > max)
			{
				max = dp[i][j];
				y = i;
				x = j;
			}
		}
	}

	// Step 4: Mark the biggest square in the map	
	for (int i = y; i > y - max; i--)
		for (int j = x; j > x - max; j--)
			m->map[i][j] = m->f;
	
	// Step 5: Print the map
	for (int i = 0; i < m->rows; i++)
		fputs(m->map[i], stdout);

	// Step 6: Free allocated memory
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
	// opens the file or use stdin if no file
	FILE *f = path ? fopen(path, "r") : stdin;
	if (!f)
	{
		fprintf(stderr, "map error\n");
		return ;
	}
	t_map m = {0};
	// Parse header and map
	if (!parse_header(&m, f) || !read_map(&m, f))
		fprintf(stderr, "map error\n");
	else
		// if valid calls solve, otherwise error (above)
		solve(&m);
	// close the file if not stdin
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

