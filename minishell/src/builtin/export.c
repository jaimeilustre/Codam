/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 17:01:23 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/09 17:39:14 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"
#include "utils.h"
#include "exec.h"

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
	sort_list(&sorted_list, ft_strcmp);
	iter_list(&sorted_list, print_exp_var);
	shallow_free_list(&sorted_list);
	return (E_SUCCESS);
}

static bool	add_to_env(t_cstr full_entry, t_cstr sep, t_alist *env_lst)
{
	t_str	key;

	key = ft_substr(full_entry, 0, sep - full_entry);
	if (key == NULL || !ms_setenv(env_lst, key, full_entry, ENV_EXPORT))
		return (free(key), false);
	return (free(key), true);
}

static t_exit_code	update_env(t_str *argv, t_alist *env_lst)
{
	t_str		ch;
	t_exit_code	exit_code;

	exit_code = E_SUCCESS;
	while (*argv)
	{
		ch = ft_strchrnul(*argv, '=');
		if (!validate_name(*argv, ch - *argv))
		{
			exit_code = E_GEN_ERR;
			ms_error(INVALID_ID, EXP_NAME, *argv);
		}
		else if (!add_to_env(*argv, ch, env_lst))
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
