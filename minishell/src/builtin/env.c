/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 16:22:28 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/14 17:54:43 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	env(int argc, t_str *argv, t_alist *env_lst)
{
	t_str	*items;

	(void)argc;
	(void)argv;
	items = env_lst->items;
	while (*items)
	{
		ft_putendl_fd(*items, STDOUT);
		++items;
	}
	return (0);
}
