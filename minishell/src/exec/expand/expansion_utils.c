/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/14 16:21:36 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:35:31 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

#include "exec.h"
#include "list.h"
#include "ms_string.h"

/* Hidden files are only included if the wildcard starts with . */
bool	any_file(t_cstr wildcard, t_cstr name)
{
	return (*wildcard == '.' || *name != '.');
}

t_cstr	next_token(t_cstr arg, t_cstr tokens)
{
	while (!ft_strchr(tokens, *arg))
		++arg;
	return (arg);
}

t_cstr	consume_chars(t_cstr str, const char c)
{
	while (*str == c)
		++str;
	return (str);
}

bool	has_strstr(t_cstr *str, t_cstr ptrn, t_strstr strstr, t_needle ndl)
{
	t_cstr	start;

	start = *str;
	*str = strstr(*str, ptrn);
	if (*str == NULL)
		return (false);
	else if (ndl == N_START)
		return (*str == start);
	else if (ndl == N_END)
		return (*(*str + ft_strlen(ptrn)) == '\0');
	return (true);
}

void	free_exp(t_exp *exp)
{
	exp->ls_off = 0;
	exp->sb_off = 0;
	free_strb(&exp->sb);
	free_list(&exp->ls);
}
