/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 16:17:08 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/21 16:08:43 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include "ms_string.h"

typedef enum e_env_flag
{
	ENV_NONE = 0x0,							/* Empty flag */
	ENV_HIDDEN = 0x1,						/* Key is set but remains hidden */
	ENV_UNSET = 0x2,						/* Key is unset but not deleted */
	ENV_EXPORT = 0x4,						/* Is an export variable */
	ENV_UNLIST = (ENV_HIDDEN | ENV_UNSET)	/* Unlisted variable */
}	t_env_fl;

typedef struct s_alist
{
	t_str		*items;
	t_env_fl	*flags;
	int			capacity;
	int			size;
}	t_alist;

typedef int	(*t_compare)(t_cstr, t_cstr);

bool	init_list(t_alist *list, int capacity);
void	free_list(t_alist *list);
bool	add_to_list(t_alist *list, t_str item, t_env_fl flag);
int		find_item_in_list(t_alist *list, t_cstr item, t_compare comp);
bool	remove_index_from_list(t_alist *list, int i);
bool	duplicate_list(t_alist *dst, t_alist *src, t_env_fl in, t_env_fl ex);
void	sort_list(t_alist *list, t_compare comp);
void	iter_list(t_alist *list, void (*f)(t_cstr, t_env_fl));

#endif
