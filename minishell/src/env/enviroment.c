/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enviroment.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 11:59:32 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/20 11:04:39 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "ms_string.h"
#include "list.h"

static int	cmp_env_var(t_cstr a, t_cstr b)
{
	size_t	len;

	len = ft_strlen(b);
	if (ft_strncmp(a, b, len) == 0 && (a[len] == '=' || a[len] == '\0'))
		return (0);
	return (1);
}

bool	init_env(t_alist *env_lst, t_str *env)
{
	t_str	env_var;

	init_list(env_lst, 100);
	while (*env)
	{
		env_var = ft_strdup(*env);
		if (env_var == NULL)
			return (free_args(env_lst->items), false);
		add_to_list(env_lst, env_var);
		++env;
	}
	return (true);
}

t_cstr	ms_getenv(t_alist *env_lst, t_cstr env_var)
{
	int		i;
	t_cstr	val;

	i = find_item_in_list(env_lst, env_var, cmp_env_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(env_lst->items[i], '=');
	if (*val == '=')
		return (val + 1);
	return (val);
}

/// @brief Add or replace value (key=value) in the current
/// @param env_lst	The enviroment variables list
/// @param env_var	The key to look for.
/// @param value	The key value pair that will replace the previous occurence
///					or add as an new entry.
/// @return			Return true if successfully updated the env_lst.
bool	ms_setenv(t_alist *env_lst, t_cstr env_var, t_cstr value)
{
	int		i;
	t_str	env_val;

	env_val = ft_strdup(value);
	if (env_val == NULL)
		return (false);
	i = find_item_in_list(env_lst, env_var, cmp_env_var);
	if (i == -1 && add_to_list(env_lst, env_val))
	{
		return (true);
	}
	else if (i > 0)
	{
		free(env_lst->items[i]);
		env_lst->items[i] = env_val;
		return (true);
	}
	return (free(env_val), false);
}

bool	ms_unset_env(t_alist *env_lst, t_cstr env_var)
{
	return (remove_index_from_list(
			env_lst, find_item_in_list(env_lst, env_var, cmp_env_var)
		));
}
