/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 11:31:42 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/04 17:28:40 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_leftover(char *str)
{
	char			*new_line_ind;
	char			*new_leftover;
	unsigned int	start_index;
	size_t			leftover_len;

	if (!str)
		return (NULL);
	new_line_ind = ft_strchr(str, '\n');
	if (!new_line_ind)
	{
		free(str);
		return (NULL);
	}
	start_index = new_line_ind - str + 1;
	leftover_len = ft_strlen(new_line_ind + 1);
	new_leftover = ft_substr(str, start_index, leftover_len);
	free(str);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buffer;
	char		*full_line;
	int			bytes_read;
	size_t		line_len;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	if (!leftover)
		leftover = ft_strdup("");
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		if (!leftover)
		{
			free(buffer);
			return (NULL);
		}
		if (ft_strchr(leftover, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	if (!leftover || !*leftover)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line_len = 0;
	while (leftover[line_len] && leftover[line_len] != '\n')
		line_len++;
	if (leftover[line_len] == '\n')
		line_len++;
	full_line = ft_substr(leftover, 0, line_len);
	if (!full_line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	leftover = update_leftover(leftover);
	return (full_line);
}
