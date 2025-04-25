/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 11:52:20 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:59:01 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>

#include "libft.h"

#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "ms_error.h"
#include "utils.h"

static void	store_abs_path_in_pwd(t_alist *env_lst, t_cstr pwd_key)
{
	t_path	cwd[PATH_MAX];
	t_str	env_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		*cwd = '\0';
	env_pwd = join_pair(pwd_key, cwd, "=");
	ms_setenv(env_lst, pwd_key, env_pwd, ENV_NONE);
	free(env_pwd);
}

static int	change_directory(t_cstr path, t_alist *env_lst)
{
	store_abs_path_in_pwd(env_lst, V_OLDPWD);
	if (chdir(path) == -1)
		return (ms_error(PERROR, CD_NAME, (t_str)path), E_GEN_ERR);
	store_abs_path_in_pwd(env_lst, V_PWD);
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
	if (str_copy != NULL && change_directory(str_copy, env_lst) == E_SUCCESS)
	{
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
