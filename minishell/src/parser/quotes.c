/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/07 07:42:52 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/11 10:25:45 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/*Checking for unclosed quotes before tokenization*/
int	check_quotes(const char *input)
{
	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			input = ft_strchrnul(input + 1, *input);
			if (*input == '\0')
			{
				ft_putendl_fd("Unclosed quote", 2);
				return (-1);
			}
		}
		++input;
	}
	return (0);
}

/*Reading single or double quotes*/
int	read_quotes(t_source *src, long start)
{
	char	quote_type;

	quote_type = src->buffer[start];
	src->curpos++;
	while (src->curpos < src->bufsize)
	{
		if (src->buffer[src->curpos] == quote_type)
		{
			src->curpos++;
			break ;
		}
		src->curpos++;
	}
	return (0);
}
