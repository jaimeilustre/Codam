/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 19:47:45 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:57:13 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

# include "list.h"
# include "ms_string.h"

# define STDIN	STDIN_FILENO
# define STDOUT	STDOUT_FILENO
# define STDERR	STDERR_FILENO

# define MINISHELL	"minishell"

# define V_PWD		"PWD"
# define V_OLDPWD	"OLDPWD"
# define V_HOME		"HOME"
# define V_SHLVL	"SHLVL"
# define V_EXIT		"?"

/* Prompt */

t_str	cmd_prompt(t_cstr prompt);

/* Environment */

bool	init_env(t_alist *env_lst, t_str *env);
bool	ms_decl_setenv(t_alist *env_lst, t_cstr key, t_cstr value, t_env_fl fl);
bool	ms_setenv(t_alist *env_lst, t_cstr key, t_cstr value, t_env_fl flag);
t_cstr	ms_getenv(t_alist *env_lst, t_cstr env_var);
bool	ms_unset_env(t_alist *env_lst, t_cstr env_var);

/* Validate */

bool	validate_name(t_cstr key, size_t len);

#endif
