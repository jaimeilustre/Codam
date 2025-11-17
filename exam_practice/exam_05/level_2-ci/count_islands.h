/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_islands.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/09 15:08:42 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/09 15:11:21 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COUNT_ISLANDS_HPP
# define COUNT_ISLANDS_HPP

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