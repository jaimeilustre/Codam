/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 11:31:42 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/01 15:10:00 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	*leftover;
	char		*buffer;
	char		*full_line;
	int			bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		if (ft_strchr(leftover, '\n'))
			break ;
	}
}
