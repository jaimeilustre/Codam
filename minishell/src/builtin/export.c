/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 17:01:23 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 18:00:55 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "builtin.h"
#include "exec.h"
#include "list.h"
#include "minishell.h"
#include "ms_error.h"

static void	print_exp_var(t_cstr item, t_env_fl flag)
{
	const char	*prepend = "declare -x ";

	(void)flag;
	ft_putstr_fd((t_str)prepend, STDOUT);
	ft_putendl_fd((t_str)item, STDOUT);
}

static t_exit_code	print_env(t_alist *env_lst)
{
	t_alist	sorted_list;

	if (!duplicate_list(&sorted_list, env_lst, ENV_EXPORT, ENV_HIDDEN))
		return (ms_error(PERROR, NULL, NULL), E_GEN_ERR);
	sort_list(&sorted_list, 0, sorted_list.size - 1, ft_strcmp);
	iter_list(&sorted_list, print_exp_var);
	shallow_free_list(&sorted_list);
	return (E_SUCCESS);
}

static bool	add_to_env(t_cstr entry, t_cstr sep, t_alist *env_lst, bool append)
{
	t_str	key;
	t_cstr	prev;
	t_strb	sb;

	key = ft_substr(entry, 0, (sep - entry));
	if (key == NULL)
		return (false);
	prev = ms_getenv(env_lst, key);
	if (!append || prev == NULL)
	{
		append = ms_setenv(env_lst, key, entry, ENV_EXPORT);
		return (free(key), append);
	}
	append = (init_strb(&sb, 128)
			&& append_strb(&sb, key, ft_strlen(key))
			&& append_strb(&sb, "=", 1)
			&& append_strb(&sb, prev, ft_strlen(prev))
			&& append_strb(&sb, sep + 1, ft_strlen(sep + 1))
			&& shrink_strb(&sb)
			&& ms_setenv(env_lst, key, sb.str, ENV_EXPORT));
	return (free(key), free_strb(&sb), append);
}

static t_exit_code	update_env(t_str *argv, t_alist *env_lst)
{
	t_str		ch;
	t_exit_code	exit_code;
	bool		append;

	exit_code = E_SUCCESS;
	while (*argv)
	{
		ch = ft_strchrnul(*argv, '=');
		append = (ch != *argv) && (*(ch - 1) == '+');
		if (append)
			ft_strcpy(ch - 1, ch);
		if (!validate_name(*argv, (ch - append - *argv)))
		{
			exit_code = E_GEN_ERR;
			ms_error(INVALID_ID, EXP_NAME, *argv);
		}
		else if (!add_to_env(*argv, ch - append, env_lst, append))
		{
			exit_code = E_GEN_ERR;
			ms_error(PERROR, EXP_NAME, *argv);
		}
		++argv;
	}
	return (exit_code);
}

int	export(int argc, t_str *argv, void *env_lst)
{
	if (argc < 2)
		return (print_env(env_lst));
	return (update_env(argv + 1, env_lst));
}
