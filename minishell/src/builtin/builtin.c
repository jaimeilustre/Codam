/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 16:01:14 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/28 18:18:47 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

#define MAX_SIZE 7

t_blt_func	find_builtin(t_str cmd)
{
	int					i;
	static t_builtin	builtins[MAX_SIZE] = {
		(t_builtin){"echo", echo},
		(t_builtin){"env", env},
		(t_builtin){"export", export},
		(t_builtin){"unset", unset},
		(t_builtin){"pwd", pwd},
		(t_builtin){"cd", cd},
		(t_builtin){"exit", ms_exit}
	};

	i = 0;
	while (i < MAX_SIZE)
	{
		if (ft_strcmp(cmd, builtins[i].name) == 0)
			return (builtins[i].blt_func);
		++i;
	}
	return (NULL);
}
