/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/21 12:41:49 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/08 14:30:33 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "exec.h"

static void	update_shlvl(t_alist *env_lst)
{
	t_cstr	shlvl;
	t_str	val;

	shlvl = ms_getenv(env_lst, V_SHLVL);
	if (shlvl == NULL || *shlvl == '\0')
	{
		ms_setenv(env_lst, V_SHLVL, V_SHLVL"=1", ENV_EXPORT);
		return ;
	}
	val = ft_itoa(ft_atoi(shlvl) + 1);
	if (val == NULL)
		return ;
	shlvl = join_pair(V_SHLVL, val, "=");
	if (shlvl != NULL)
		ms_setenv(env_lst, V_SHLVL, shlvl, ENV_EXPORT);
	free(val);
	free((void *)shlvl);
}

static void	update_pwd_to_cwd(t_alist *env_lst)
{
	t_path	cwd[PATH_MAX];
	t_cstr	env_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	env_pwd = join_pair(V_PWD, cwd, "=");
	if (env_pwd != NULL)
	{
		ms_setenv(env_lst, V_PWD, env_pwd, ENV_EXPORT);
		free((void *)env_pwd);
	}
}

static void	update_oldpwd(t_alist *env_lst)
{
	t_cstr	env_oldpwd;
	DIR		*dir;

	env_oldpwd = ms_getenv(env_lst, V_OLDPWD);
	if (env_oldpwd != NULL)
	{
		dir = opendir(env_oldpwd);
		if (dir != NULL)
		{
			closedir(dir);
			return ;
		}
	}
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
