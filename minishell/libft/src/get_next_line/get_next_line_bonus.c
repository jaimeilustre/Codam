/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:13:25 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 17:41:48 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static void	clear_buffer(t_buffer *data)
{
	free(data->buffer);
	data->buffer = NULL;
	data->start = NULL;
	data->bytes = -1;
}

static bool	init_buffer(t_buffer *data, ssize_t size)
{
	if (data->buffer != NULL)
		return (true);
	data->buffer = malloc((size + 1) * sizeof(char));
	if (data->buffer == NULL)
		return (false);
	data->start = data->buffer;
	*(data->buffer) = '\0';
	data->bytes = 0;
	return (true);
}

static bool	append_to(t_buffer *line, t_buffer *read_data)
{
	char	*new_line;
	char	*end;
	ssize_t	sub_len;

	end = ft_strchrnul(read_data->start, '\n');
	if (*end == '\n')
		++end;
	sub_len = (end - read_data->start);
	new_line = malloc((line->bytes + sub_len + 1) * sizeof(char));
	if (new_line == NULL)
		return (line->bytes = -1, false);
	ft_memmove(new_line, line->buffer, line->bytes);
	ft_memmove(new_line + line->bytes, read_data->start, sub_len);
	line->bytes += sub_len;
	read_data->bytes -= sub_len;
	new_line[line->bytes] = '\0';
	free(line->buffer);
	line->buffer = new_line;
	read_data->start = end;
	return (true);
}

static bool	read_fd(int fd, t_buffer *read_data)
{
	if (*(read_data->start) != '\0')
		return (true);
	read_data->bytes = read(fd, read_data->buffer, BUFFER_SIZE);
	if (read_data->bytes == -1 || read_data->bytes == 0)
		return (false);
	read_data->buffer[read_data->bytes] = '\0';
	read_data->start = read_data->buffer;
	return (true);
}

char	*get_next_line_bonus(int fd)
{
	static t_buffer	read_data[MAX_FD];
	t_buffer		line;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	line.buffer = NULL;
	if (BUFFER_SIZE <= 0 || !init_buffer(&read_data[fd], BUFFER_SIZE)
		|| !init_buffer(&line, 0))
		return (clear_buffer(&read_data[fd]), NULL);
	while (read_fd(fd, &read_data[fd]) && append_to(&line, &read_data[fd])
		&& line.buffer[line.bytes - 1] != '\n')
		;
	if (read_data[fd].bytes == -1
		|| (read_data[fd].bytes == 0 && line.bytes == 0) || line.bytes == -1)
		return (clear_buffer(&line), clear_buffer(&read_data[fd]), NULL);
	return (line.buffer);
}
