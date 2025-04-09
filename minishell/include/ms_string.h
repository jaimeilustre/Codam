/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_string.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 14:49:22 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/28 11:08:39 by jboon         ########   odam.nl         */
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

typedef struct s_strb
{
	t_str	str;
	size_t	size;
	size_t	capacity;

}	t_strb;

void	free_args(t_str *words);
bool	is_empty_cmd(t_cstr str);
void	append_to_path(t_str full_path, t_cstr path, t_cstr cmd);
size_t	count_args(t_str *words);
int		ft_strcmp(t_cstr s1, t_cstr s2);

/* String Builder */

bool	init_strb(t_strb *sb, size_t capacity);
void	free_strb(t_strb *sb);
bool	append_strb(t_strb *sb, t_cstr src, size_t len);
bool	shrink_strb(t_strb *sb);

#endif
