/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bsq.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 13:41:44 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/06 15:17:02 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_HPP
# define BSQ_HPP

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_map
{
	int	rows;
	int	cols;
	char	e; // empty characters
	char	o; // obstacles
	char	f; // full characters
	char	**map;
}	t_map;

#endif