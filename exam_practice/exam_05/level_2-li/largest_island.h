/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_islands.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/09 15:08:42 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/17 10:21:33 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LARGEST_ISLAND_HPP
# define LARGEST_ISLAND_HPP

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_map
{
	int	height;
	int	width;
	char **grid;
}	t_map;

#endif