/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/07 07:42:52 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/07 09:25:53 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/*Checking for unclosed quotes before tokenization*/
int	check_quotes(const char *input)
{
	int		i;
	char	quote_type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote_type = input[i];
			i++;
			while (input[i] && input[i] != quote_type)
				i++;
			if (!input[i])
			{
				ft_putendl_fd("Unclosed quote", 2);
				return (-1);
			}
		}
		i++;
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
