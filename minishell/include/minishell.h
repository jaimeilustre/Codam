/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 19:47:45 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/13 11:14:54 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "ms_string.h"

# define STDIN	STDIN_FILENO
# define STDOUT	STDOUT_FILENO
# define STDERR	STDERR_FILENO

# define MINISHELL "minishell"

void	interative_mode(int signo);
t_str	cmd_prompt(t_cstr prompt);
t_str	find_cmd(t_str cmd);
void	exe_cmd(t_str cmd, t_str *env);

#endif
