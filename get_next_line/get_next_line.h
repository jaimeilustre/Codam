/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 11:31:32 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/01 14:08:01 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef	BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif