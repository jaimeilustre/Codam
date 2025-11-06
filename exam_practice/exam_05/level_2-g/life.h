/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   life.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 10:58:51 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/06 11:04:23 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_game
{
	int	width;
	int	height;
	int	iterations;
	char	**map;
}	t_game;

#endif