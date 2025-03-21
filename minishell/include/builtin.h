/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 15:54:48 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/14 17:17:57 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "list.h"
# include "ms_string.h"

# define CD_NAME "cd"

typedef int	(*t_blt_func)(int, t_str *, t_alist *);

typedef struct s_builtin
{
	t_str		name;
	t_blt_func	blt_func;
}	t_builtin;

t_blt_func	find_builtin(t_str cmd);
int			echo(int argc, t_str *argv, t_alist *env_lst);
int			env(int argc, t_str *argv, t_alist *env_lst);
int			export(int argc, t_str *argv, t_alist *env_lst);
int			unset(int argc, t_str *argv, t_alist *env_lst);
int			pwd(int argc, t_str *argv, t_alist *env_lst);
int			cd(int argc, t_str *argv, t_alist *env_lst);

#endif
