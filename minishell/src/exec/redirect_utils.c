/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 14:04:17 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/18 13:47:44 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <stdbool.h>

bool	store_std_fd(int new_fd[RE_MAX_FD])
{
	static const int	std[RE_MAX_FD] = {STDIN, STDOUT};
	int					i;
	int					fd;

	i = 0;
	while (i < RE_MAX_FD)
	{
		fd = dup(std[i]);
		if (fd == -1)
			return (false);
		new_fd[i] = fd;
		++i;
	}
	return (true);
}
