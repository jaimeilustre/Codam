/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/06 09:25:10 by jilustre      #+#    #+#                 */
/*   Updated: 2024/11/07 13:23:44 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_fd(int fd, char *leftover)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(leftover), NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		if (!leftover)
			return (free(buffer), NULL);
		if (ft_strchr(leftover, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0)
		return (free(leftover), NULL);
	return (leftover);
}

static char	*get_line(char *leftover)
{
	size_t	line_len;
	char	*full_line;

	line_len = 0;
	while (leftover[line_len] && leftover[line_len] != '\n')
		line_len++;
	if (leftover[line_len] == '\n')
		line_len++;
	full_line = ft_substr(leftover, 0, line_len);
	if (!full_line || *full_line == '\0')
		return (NULL);
	return (full_line);
}

static char	*update_leftover(char *str)
{
	char			*new_line_ind;
	char			*new_leftover;
	unsigned int	start_index;
	size_t			leftover_len;

	if (!str)
		return (NULL);
	new_line_ind = ft_strchr(str, '\n');
	if (!new_line_ind)
		return (free(str), NULL);
	start_index = new_line_ind - str + 1;
	leftover_len = ft_strlen(new_line_ind + 1);
	new_leftover = ft_substr(str, start_index, leftover_len);
	free(str);
	if (new_leftover && *new_leftover == '\0')
		return (free(new_leftover), NULL);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*full_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftover)
		leftover = ft_strdup("");
	leftover = read_fd(fd, leftover);
	if (!leftover || !*leftover)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	full_line = get_line(leftover);
	if (!full_line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	leftover = update_leftover(leftover);
	return (full_line);
}