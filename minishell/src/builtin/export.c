/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 17:01:23 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/17 17:40:25 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ms_error.h"
#include "utils.h"

static void	print_env(t_alist *env_lst)
{
	static t_cstr	prepend = "declare -x ";
	int				i;
	t_alist			tmp_list;

	i = 0;
	init_list(&tmp_list, env_lst->size);
	while (i < env_lst->size)
	{
		add_to_list(&tmp_list, env_lst->items[i]);
		++i;
	}
	i = 0;
	sort_list(&tmp_list, ft_strcmp);
	while (i < tmp_list.size)
	{
		ft_putstr_fd((char *)prepend, STDOUT);
		ft_putendl_fd(tmp_list.items[i], STDOUT);
		++i;
	}
	free(tmp_list.items);
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
				ms_setenv(env_lst, key, *argv);
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
