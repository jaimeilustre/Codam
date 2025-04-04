/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_string.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 14:49:22 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/20 12:37:13 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRING_H
# define MS_STRING_H

# include <stdbool.h>
# include <stddef.h>
# include <limits.h>

typedef char*		t_str;
typedef const char*	t_cstr;
typedef char		t_path;

void	free_args(t_str *words);
bool	is_empty_cmd(t_cstr str);
void	append_to_path(t_str full_path, t_cstr path, t_cstr cmd);
size_t	count_args(t_str *words);
int		ft_strcmp(t_cstr s1, t_cstr s2);

#endif
