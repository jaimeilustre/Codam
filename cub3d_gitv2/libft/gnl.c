/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:01:04 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 17:01:39 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//Util function that copies string from S2 to S1. S1 will be freed after
//this operation and a new allocated string will be returned with s1 and s2
//concaternated.
static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1[i])
		newstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		newstr[j++] = s2[i++];
	newstr[j] = '\0';
	free(s1);
	return (newstr);
}

static char	*read_line(int fd, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		s;

	if (!line)
		line = ft_strdup("\0");
	if (!line)
		return (NULL);
	buffer[0] = '\0';
	s = 1;
	while (s != 0 && !ft_strrchr(buffer, '\n'))
	{
		s = read(fd, buffer, BUFFER_SIZE);
		if (s < 0)
			return (free(line), NULL);
		buffer[s] = '\0';
		line = ft_strjoin_free(line, buffer);
		if (!line)
			return (NULL);
	}
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

// new one that deletes newline
static char	*take_string(char *str)
{
	size_t	i;
	size_t	len;
	char	*nstr;

	i = 0;
	len = 0;
	while (str[len] != '\n' && str[len])
		len++;
	if (str[len] == '\n')
		len++;
	nstr = malloc(len);
	if (!nstr)
		return (NULL);
	while (str[i] != '\n' && str[i])
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

//Takes the left overs from the complete string. Everything after the newline
//should be copied to a new string and the old leftover string should be freed
//correctly.
static char	*take_left(char *str)
{
	size_t	i;
	size_t	len;
	char	*nstr;

	i = 0;
	len = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	len = ft_strlen(&str[i]);
	nstr = malloc(len + 1);
	if (!nstr)
		return (free(str), NULL);
	ft_strcpy(nstr, str + i);
	free(str);
	return (nstr);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > __INT_MAX__)
		return (NULL);
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	buff = take_string(line);
	if (!buff)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = take_left(line);
	return (buff);
}
