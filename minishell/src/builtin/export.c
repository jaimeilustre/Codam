/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 17:01:23 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/21 16:08:43 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"
#include "utils.h"

static void	print_exp_var(t_cstr item, t_env_fl flag)
{
	static t_cstr	prepend = "declare -x ";

	(void)flag;
	ft_putstr_fd((t_str)prepend, STDOUT);
	ft_putendl_fd((t_str)item, STDOUT);
}

static void	print_env(t_alist *env_lst)
{
	t_alist			sorted_list;

	if (!duplicate_list(&sorted_list, env_lst, ENV_EXPORT, ENV_HIDDEN))
		return (ms_error(PERROR, NULL, NULL));
	sort_list(&sorted_list, ft_strcmp);
	iter_list(&sorted_list, print_exp_var);
	free(sorted_list.items);
	free(sorted_list.flags);
}

static void	update_env(t_str *argv, t_alist *env_lst)
{
	t_str	key;
	t_str	ch;

	while (*argv)
	{
		ch = ft_strchrnul(*argv, '=');
		if (validate_name(*argv, ch - *argv))
		{
			key = ft_substr(*argv, 0, ch - *argv);
			if (key != NULL)
			{
				ms_setenv(env_lst, key, *argv, ENV_EXPORT);
				free(key);
			}
			else
				ms_error(PERROR, "export", *argv);
		}
		else
			ms_error(INVALID_ID, "export", *argv);
		++argv;
	}
}

int	export(int argc, t_str *argv, t_alist *env_lst)
{
	if (argc < 2)
		print_env(env_lst);
	else
		update_env(argv + 1, env_lst);
	return (EXIT_SUCCESS);
}
