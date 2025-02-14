/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_string.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 14:49:22 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/13 11:18:38 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRING_H
# define MS_STRING_H

# include <stdbool.h>

typedef char*		t_str;
typedef const char*	t_cstr;

void	free_split(t_str *words);
bool	is_empty_cmd(t_cstr str);
void	append_to_path(t_str full_path, t_cstr path, t_cstr cmd);

#endif
