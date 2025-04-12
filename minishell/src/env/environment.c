/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 11:59:32 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/09 17:24:58 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "minishell.h"
#include "ms_string.h"
#include "list.h"
#include "utils.h"

static int	cmp_env_var(t_cstr a, t_cstr b)
{
	size_t	len;

	len = ft_strlen(b);
	if (ft_strncmp(a, b, len) == 0 && (a[len] == '=' || a[len] == '\0'))
		return (0);
	return (1);
}

/* Declare and init or override the environment variable */
bool	ms_decl_setenv(t_alist *env_lst, t_cstr key, t_cstr value, t_env_fl fl)
{
	int		i;
	t_str	env_val;

	env_val = ft_strdup(value);
	if (env_val == NULL)
		return (false);
	fl |= (ft_strchr(value, '=') == NULL) * ENV_UNSET;
	i = find_item_in_list(env_lst, key, cmp_env_var);
	if (i == -1)
	{
		if (add_to_list(env_lst, env_val, fl))
			return (true);
		return (free(env_val), false);
	}
	free(env_lst->items[i]);
	env_lst->items[i] = env_val;
	env_lst->flags[i] = fl;
	return (true);
}

/* Return the pointer to the enviroment variable (do not free!) */
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
/// @param env_lst The environment variables list
/// @param key The key to look for.
/// @param value The key value pair that will replace the previous occurence
/// @param flag Type of environment variable
///				or add as an new entry.
/// @return			Return true if successfully updated the env_lst.
bool	ms_setenv(t_alist *env_lst, t_cstr key, t_cstr value, t_env_fl flag)
{
	int		i;
	t_str	env_val;

	if (!validate_name(key, ft_strlen(key)))
		return (false);
	env_val = ft_strdup(value);
	if (env_val == NULL)
		return (false);
	flag |= (ft_strchr(value, '=') == NULL) * ENV_UNSET;
	i = find_item_in_list(env_lst, key, cmp_env_var);
	if (i == -1 && add_to_list(env_lst, env_val, flag))
		return (true);
	else if (i > 0)
	{
		if ((flag & ENV_UNSET) == ENV_UNSET)
			return (free(env_val), true);
		free(env_lst->items[i]);
		env_lst->items[i] = env_val;
		env_lst->flags[i] = env_lst->flags[i] | flag;
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
