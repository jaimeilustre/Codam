/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 16:17:08 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/14 17:17:44 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include "ms_string.h"

typedef struct s_alist
{
	t_str	*items;
	int		capacity;
	int		size;
}	t_alist;

typedef int	(*t_compare)(t_cstr, t_cstr);

bool	init_list(t_alist *list, int capacity);
bool	add_to_list(t_alist *list, t_str item);
int		find_item_in_list(t_alist *list, t_cstr item, t_compare comp);
bool	remove_index_from_list(t_alist *list, int i);
void	sort_list(t_alist *list, t_compare comp);

#endif
