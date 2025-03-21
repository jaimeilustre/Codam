/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/17 12:02:09 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/13 15:38:52 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "ms_string.h"

void	swap_ptr(void **a, void **b);
void	swapi(int *a, int *b);
t_cstr	join_pair(t_cstr left, t_cstr right, char *sep);

#endif
