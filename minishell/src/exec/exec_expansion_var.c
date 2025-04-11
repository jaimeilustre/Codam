/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_expansion_var.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 13:13:54 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/11 10:52:42 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "exec.h"

/* Supports $? only, but could be extended for $$, $0, ect. */
static bool	is_special_variable(const char c)
{
	return (ft_strchr("?", c) != NULL);
}

static t_cstr	get_end_of_name(t_cstr end)
{
	if (is_special_variable(*end))
		return (end + 1);
	else if (ft_isalpha(*end) || *end == '_')
	{
		++end;
		while (ft_isalnum(*end) || *end == '_')
			++end;
	}
	return (end);
}

/* Expand the variable to its value and append that to sb */
bool	expand_variable(t_strb *sb, t_cstr *var, t_alist *env_lst)
{
	t_cstr	end;
	t_cstr	value;
	t_str	key;

	end = get_end_of_name((*var) + 1);
	if (end == (*var) + 1)
		return (append_strb(sb, "$", 1));
	key = ft_substr(*var, 0, end - *var);
	if (key == NULL)
		return (false);
	value = ms_getenv(env_lst, key + 1);
	*var = (end - 1);
	free(key);
	return (value == NULL || append_strb(sb, value, ft_strlen(value)));
}
