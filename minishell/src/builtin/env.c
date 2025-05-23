/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 16:22:28 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:55:34 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "exec.h"
#include "list.h"
#include "minishell.h"
#include "ms_string.h"

static void	print_env_var(t_cstr item, t_env_fl flag)
{
	if ((flag & ENV_EXPORT) == 0 || (flag & ENV_UNLIST) != 0)
		return ;
	ft_putendl_fd((t_str)item, STDOUT);
}

int	env(int argc, t_str *argv, void *env_lst)
{
	(void)argc;
	(void)argv;
	iter_list(env_lst, print_env_var);
	return (E_SUCCESS);
}
