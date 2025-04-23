/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/14 16:31:54 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/14 18:38:33 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"
#include "exec.h"
#include "ms_string.h"

/*
Add the dir entry to ls if it matches with the pattern.
Returns false on errror.
*/
static bool	add_dir_entry(t_cstr d_name, t_cstr pattern, size_t ln, t_alist *ls)
{
	t_str	dup_name;
	t_cstr	str;

	str = d_name;
	if (any_file(pattern, d_name)
		&& has_strstr(&str, pattern, ft_strstr, N_START))
	{
		ln = (str - d_name) + ln;
		dup_name = ft_strdup(d_name);
		if (dup_name == NULL || !add_to_list(ls, dup_name, ln))
			return (free(dup_name), false);
	}
	return (true);
}

static bool	read_dir_entries(t_cstr pattern, t_alist *ls)
{
	DIR				*dir;
	struct dirent	*ent;
	size_t			len;

	len = ft_strlen(pattern);
	dir = opendir(".");
	while (dir != NULL)
	{
		errno = 0;
		ent = readdir(dir);
		if (ent == NULL || !add_dir_entry(ent->d_name, pattern, len, ls))
			break ;
	}
	if (errno != 0)
		return (closedir(dir), false);
	return (closedir(dir) == 0);
}

void	filter_entries(t_cstr pattern, t_exp *exp, t_needle ndl)
{
	int			i;
	t_cstr		substr;
	t_strstr	strstr;
	size_t		len;

	i = exp->ls_off;
	len = ft_strlen(pattern);
	if (ndl == N_END)
		strstr = ft_strrstr;
	else
		strstr = ft_strstr;
	while (i < exp->ls.size)
	{
		substr = (exp->ls.items[i] + exp->ls.flags[i]);
		if (has_strstr(&substr, pattern, strstr, ndl))
		{
			exp->ls.flags[i] = (substr - exp->ls.items[i]) + len;
			++i;
		}
		else
			remove_index_from_list(&exp->ls, i);
	}
}

bool	expand_wildcard(t_cstr *ch, t_exp *exp)
{
	t_cstr	end;
	t_str	wc;
	int		prev;

	prev = exp->sb.size;
	end = consume_chars(*ch, **ch);
	if (!append_strb(&exp->sb, *ch, end - *ch))
		return (false);
	wc = ft_strchr((exp->sb.str + prev), **ch);
	*wc = '\0';
	if (exp->sb_off > 0)
		filter_entries((exp->sb.str + exp->sb_off), exp, N_MID);
	else if (!read_dir_entries(exp->sb.str, &exp->ls))
		return (false);
	*wc = '*';
	exp->sb_off = (wc - exp->sb.str) + (end - *ch);
	*ch = end - 1;
	return (true);
}

bool	expand_var_wildcards(int curr, t_exp *exp)
{
	t_str	wc;
	t_cstr	end;

	wc = ft_strchr(exp->sb.str + curr, '*');
	while (wc)
	{
		*wc = '\0';
		if (exp->sb_off > 0)
			filter_entries((exp->sb.str + exp->sb_off), exp, N_MID);
		else if (!read_dir_entries(exp->sb.str, &exp->ls))
			return (false);
		else
			exp->sb_off = 0;
		*wc = '*';
		end = consume_chars(wc, *wc);
		exp->sb_off += (end - (exp->sb.str + exp->sb_off));
		wc = ft_strchr(end, '*');
	}
	return (true);
}
