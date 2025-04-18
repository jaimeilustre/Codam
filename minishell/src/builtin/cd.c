/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 11:52:20 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/15 19:26:06 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include "libft.h"
#include "builtin.h"
#include "minishell.h"
#include "ms_error.h"
#include "utils.h"
#include "exec.h"

static int	change_directory(t_cstr path, t_alist *env_lst)
{
	t_path	prev_cwd[PATH_MAX];
	t_cstr	env_pwd;
	t_cstr	env_oldpwd;

	if (getcwd(prev_cwd, PATH_MAX) == NULL)
	{
		ms_error(PERROR, CD_NAME, NULL);
		*prev_cwd = '\0';
	}
	if (chdir(path) == -1)
		return (ms_error(PERROR, CD_NAME, (t_str)path), E_GEN_ERR);
	env_pwd = join_pair(V_PWD, path, "=");
	env_oldpwd = join_pair(V_OLDPWD, prev_cwd, "=");
	if (env_pwd != NULL)
		ms_setenv(env_lst, V_PWD, env_pwd, ENV_NONE);
	if (env_oldpwd != NULL)
		ms_setenv(env_lst, V_OLDPWD, env_oldpwd, ENV_NONE);
	free((void *)env_pwd);
	free((void *)env_oldpwd);
	return (E_SUCCESS);
}

static int	cd_to_home(t_alist *env_lst)
{
	t_cstr	home_dir;

	home_dir = ms_getenv(env_lst, V_HOME);
	if (home_dir != NULL)
		return (change_directory(home_dir, env_lst));
	ms_error(NO_ENV_VAR, CD_NAME, V_HOME);
	return (E_GEN_ERR);
}

static int	cd_to_oldpwd(t_alist *env_lst)
{
	t_cstr	prev_dir;
	t_str	str_copy;

	prev_dir = ms_getenv(env_lst, V_OLDPWD);
	if (prev_dir == NULL)
	{
		ms_error(NO_ENV_VAR, CD_NAME, V_OLDPWD);
		return (E_GEN_ERR);
	}
	str_copy = ft_strdup(prev_dir);
	if (change_directory(prev_dir, env_lst) == E_SUCCESS)
	{
		if (str_copy != NULL)
			ft_putendl_fd(str_copy, STDOUT);
		return (free(str_copy), E_SUCCESS);
	}
	return (free(str_copy), E_GEN_ERR);
}

int	cd(int argc, t_str *argv, void *env_lst)
{
	if (argc > 2)
	{
		ms_error(TOO_N_ARGS, CD_NAME, NULL);
		return (E_GEN_ERR);
	}
	if (argc < 2)
		return (cd_to_home(env_lst));
	else if (ft_strcmp(*(argv + 1), "-") == 0)
		return (cd_to_oldpwd(env_lst));
	else
		return (change_directory(*(argv + 1), env_lst));
	return (E_SUCCESS);
}
