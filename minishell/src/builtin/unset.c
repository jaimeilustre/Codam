/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/17 17:18:34 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/09 01:35:23 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"
#include "exec.h"

int	unset(int argc, t_str *argv, void *env_lst)
{
	if (argc > 1)
	{
		++argv;
		while (*argv)
		{
			if (validate_name(*argv, ft_strlen(*argv)))
				ms_unset_env(env_lst, *argv);
			++argv;
		}
	}
	return (E_SUCCESS);
}
