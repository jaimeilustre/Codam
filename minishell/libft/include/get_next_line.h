/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 15:12:51 by jboon         #+#    #+#                 */
/*   Updated: 2024/12/07 17:17:37 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef struct s_buffer
{
	char	*buffer;
	char	*start;
	ssize_t	bytes;
}	t_buffer;

char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);
#endif
