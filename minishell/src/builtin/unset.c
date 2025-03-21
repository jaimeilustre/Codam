/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/17 17:18:34 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/17 17:59:48 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"

int	unset(int argc, t_str *argv, t_alist *env_lst)
{
	if (argc < 2)
		return (ms_error(NO_ARGS, "unset", NULL), EXIT_FAILURE);
	++argv;
	while (*argv)
	{
		if (validate_name(*argv, ft_strlen(*argv)))
			ms_unset_env(env_lst, *argv);
		else
			ms_error(INVALID_ID, "unset", *argv);
		++argv;
	}
	return (EXIT_SUCCESS);
}
