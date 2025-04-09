/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_expansion.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/24 10:17:22 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/07 18:27:43 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "exec.h"

/* Append the string literal within the quotes to sb */
static bool	expand_single_quote(t_strb *sb, t_cstr *quote_str)
{
	t_cstr	end;
	t_cstr	start;

	start = (*quote_str) + 1;
	end = ft_strchrnul(start, '\'');
	if (*end != '\'')
		return (false);
	*quote_str = end;
	return (append_strb(sb, start, end - start));
}

/* Expand the variables within the quotes and append the string literal to sb */
static bool	expand_double_quote(t_strb *sb, t_cstr *quote_str, t_alist *env_lst)
{
	t_cstr	end;
	t_cstr	start;

	start = (*quote_str) + 1;
	if (ft_strchr(start, '\"') == NULL)
		return (false);
	end = start;
	while (*end && *end != '\"')
	{
		if (*end == '$')
		{
			if (append_strb(sb, start, end - start)
				&& expand_variable(sb, &end, env_lst))
				start = end + 1;
			else
				return (false);
		}
		++end;
	}
	*quote_str = end;
	return (append_strb(sb, start, end - start));
}

static t_cstr	handle_expansion(t_strb *sb, t_cstr *end, t_alist *env_lst)
{
	if ((**end == '\'' && !expand_single_quote(sb, end))
		|| (**end == '\"' && !expand_double_quote(sb, end, env_lst))
		|| (**end == '$' && !expand_variable(sb, end, env_lst)))
		return (NULL);
	return (*end);
}

static t_str	replace_arg(t_cstr arg, t_alist *env_lst)
{
	t_strb	sb;
	t_cstr	start;
	t_cstr	end;

	if (!init_strb(&sb, 1024))
		return (NULL);
	start = arg;
	end = start;
	while (*end)
	{
		if (ft_strchr("\'\"$", *end))
		{
			if (!append_strb(&sb, start, end - start))
				return (free_strb(&sb), NULL);
			start = handle_expansion(&sb, &end, env_lst);
			if (start == NULL)
				return (free_strb(&sb), NULL);
			++start;
		}
		++end;
	}
	if (append_strb(&sb, start, end - start) && shrink_strb(&sb))
		return (sb.str);
	free_strb(&sb);
	return (NULL);
}

bool	expand_arguments(t_str *args, t_alist *env_lst)
{
	t_str	new_arg;

	while (*args)
	{
		new_arg = replace_arg(*args, env_lst);
		if (new_arg == NULL)
			return (false);
		free(*args);
		*args = new_arg;
		++args;
	}
	return (true);
}
