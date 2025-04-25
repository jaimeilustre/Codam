/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/04 11:29:59 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:36:12 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

#include "exec.h"
#include "list.h"
#include "ms_string.h"

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
	if (sb->str == NULL && (end - start) == 0)
		return (init_strb(sb, 1));
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
	if (sb->str == NULL && (end - start) == 0)
		return (init_strb(sb, 1));
	return (append_strb(sb, start, end - start));
}

static bool	is_variable(t_cstr ch)
{
	return (*ch == '$' && *(ch + 1) != '\'' && *(ch + 1) != '\"');
}

/**
 * Expand the argument to its true string literal or if it has wildcards that
 * match a pattern it will populate the arguments list with any matching file
 * name. For the wildcards it keeps track of the last substr that has been used
 * for pattern matching. After each pattern check the index gets offsetted by
 * the len of the substr and amount of consecutive '*' that follow the wildcard.
 */
int	expand_arg(t_cstr arg, t_exp *exp, t_alist *env_lst)
{
	t_cstr	ch;
	int		prev;

	while (*arg)
	{
		ch = next_token(arg, "'\"$*");
		if (!append_strb(&exp->sb, arg, ch - arg))
			return (-1);
		prev = exp->sb.size;
		if ((*ch == '\'' && !expand_single_quote(&exp->sb, &ch))
			|| (*ch == '"' && !expand_double_quote(&exp->sb, &ch, env_lst))
			|| (*ch == '*' && !expand_wildcard(&ch, exp))
			|| (is_variable(ch) && (!expand_variable(&exp->sb, &ch, env_lst)
					|| (exp->sb.str != NULL
						&& !expand_var_wildcards(prev, exp)))))
			return (-1);
		arg = ch + (*ch != '\0');
	}
	if (exp->sb_off > 0 && exp->sb.str[exp->sb_off] != '\0')
		filter_entries(exp->sb.str + exp->sb_off, exp, N_END);
	return ((exp->ls.size - exp->ls_off) > 0);
}

bool	expand_argv(t_str *argv, t_alist *env_lst, t_alist *ls)
{
	int		status;
	t_exp	exp;

	ft_bzero(&exp, sizeof(exp));
	if (!init_list(&exp.ls, count_args(argv)))
		return (false);
	while (*argv)
	{
		exp.sb_off = -1;
		ft_bzero(&exp.sb, sizeof(t_strb));
		status = expand_arg(*argv, &exp, env_lst);
		if (status == -1
			|| (status == 0 && exp.sb.str != NULL
				&& !add_to_list(&exp.ls, exp.sb.str, 0)))
			return (free_exp(&exp), false);
		else if (status == 1)
			free_strb(&exp.sb);
		sort_list(&exp.ls, exp.ls_off, exp.ls.size - 1, ft_strcmp);
		exp.ls_off = exp.ls.size;
		++argv;
	}
	*ls = exp.ls;
	return (true);
}
