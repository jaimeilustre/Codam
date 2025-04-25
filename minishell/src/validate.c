/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/17 17:33:33 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:32:36 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "ms_string.h"

bool	validate_name(t_cstr name, size_t len)
{
	size_t	i;

	if (len == 0 || !(ft_isalpha(*name) || *name == '_'))
		return (false);
	i = 0;
	while (i < len && (ft_isalnum(name[i]) || name[i] == '_'))
		++i;
	return (i == len);
}
