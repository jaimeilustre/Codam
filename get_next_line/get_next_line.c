/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:31:42 by jilustre          #+#    #+#             */
/*   Updated: 2024/11/04 07:24:48 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_leftover(char *str)
{
	char	*new_line_ind;
	char	*new_leftover;

	if (!str)
		return (NULL);
	new_line_ind = ft_strchr(str, '\n');
	if (!new_line_ind)
	{
		free(str);
		return (NULL);
	}
	new_leftover = ft_substr(str, (new_line_ind - str) + 1, ft_strlen(new_line_ind + 1));
	free (str);
	return (new_leftover);
}

char *get_next_line(int fd)
{
	static char		*leftover;
	char			*buffer;
	char			*full_line;
	int				bytes_read;
	unsigned int	line_len;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		if (ft_strchr(leftover, '\n'))
			break ;
	}
	free(buffer);
	if (bytes_read < 0 || !leftover || !*leftover)
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
	leftover = update_leftover(leftover);
	return (full_line);
}

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int fd;
    char *line;

    // Check if a file name is provided
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    // Open the file with read-only access
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Read and print each line until get_next_line returns NULL
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line); // Print the line (already includes '\n' if present)
        free(line); // Free the line after use
    }

    // Close the file
    close(fd);
    return 0;
}
