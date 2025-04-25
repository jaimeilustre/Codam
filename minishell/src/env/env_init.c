/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/21 12:41:49 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 18:40:58 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "libft.h"

#include "exec.h"
#include "list.h"
#include "minishell.h"
#include "ms_string.h"
#include "utils.h"

static void	update_shlvl(t_alist *env_lst)
{
	t_cstr	shlvl_curr;
	t_str	shlvl_nxt;
	t_str	shlvl_nbr;

	shlvl_curr = ms_getenv(env_lst, V_SHLVL);
	if (shlvl_curr == NULL || *shlvl_curr == '\0')
	{
		ms_setenv(env_lst, V_SHLVL, V_SHLVL"=1", ENV_EXPORT);
		return ;
	}
	shlvl_nbr = ft_itoa(ft_atoi(shlvl_curr) + 1);
	if (shlvl_nbr == NULL)
		return ;
	shlvl_nxt = join_pair(V_SHLVL, shlvl_nbr, "=");
	if (shlvl_nxt != NULL)
		ms_setenv(env_lst, V_SHLVL, shlvl_nxt, ENV_EXPORT);
	free(shlvl_nbr);
	free(shlvl_nxt);
}

static void	update_pwd_to_cwd(t_alist *env_lst)
{
	t_path	cwd[PATH_MAX];
	t_str	env_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	env_pwd = join_pair(V_PWD, cwd, "=");
	if (env_pwd != NULL)
	{
		ms_setenv(env_lst, V_PWD, env_pwd, ENV_EXPORT);
		free(env_pwd);
	}
}

static void	update_oldpwd(t_alist *env_lst)
{
	t_cstr		env_oldpwd;
	struct stat	statbuf;

	env_oldpwd = ms_getenv(env_lst, V_OLDPWD);
	if (env_oldpwd != NULL
		&& stat(env_oldpwd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
		return ;
	ms_setenv(env_lst, V_OLDPWD, V_OLDPWD, (ENV_EXPORT | ENV_UNSET));
}

static void	set_base_variables(t_alist *env_lst)
{
	if (isatty(STDIN))
		ms_unset_env(env_lst, "_");
	update_oldpwd(env_lst);
	update_pwd_to_cwd(env_lst);
	update_shlvl(env_lst);
	store_exit_code(env_lst, 0);
}

bool	init_env(t_alist *env_lst, t_str *env)
{
	t_str	env_var;

	init_list(env_lst, 100);
	while (*env)
	{
		env_var = ft_strdup(*env);
		if (env_var == NULL)
			return (free_args(env_lst->items), false);
		add_to_list(env_lst, env_var, ENV_EXPORT);
		++env;
	}
	set_base_variables(env_lst);
	return (true);
}
