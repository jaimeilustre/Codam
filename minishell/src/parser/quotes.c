/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/07 07:42:52 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/17 16:50:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "exec.h"
#include "ms_error.h"

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
				ft_putendl_fd("Syntax error: near unexpected token `quote'", 2);
				return (-1);
			}
		}
		++input;
	}
	return (0);
}

/*Checking for unclosed parenthesis before tokenization*/
int	check_parenthesis(const char *input)
{
	int	depth;

	depth = 0;
	while (*input)
	{
		if (*input == '(')
			depth++;
		else if (*input == ')')
		{
			if (depth == 0)
			{
				ft_putendl_fd("Syntax error: near unexpected token `)'", 2);
				return (-1);
			}
			depth--;
		}
		input++;
	}
	if (depth > 0)
	{
		ft_putendl_fd("Syntax error: near unexpected token `('", 2);
		return (-1);
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

/*Removes quotes from the delimiter token*/
char	*remove_quotes(t_token *token)
{
	const char	*src;
	char		*result;
	char		*dest;
	char		quote_type;

	src = token->value;
	quote_type = 0;
	result = malloc(ft_strlen(src) + 1);
	if (!result)
		return (NULL);
	dest = result;
	while (*src)
	{
		if (!quote_type && (*src == '\'' || *src == '"'))
			quote_type = *src++;
		else if (quote_type && *src == quote_type)
		{
			quote_type = 0;
			src++;
		}
		else
			*dest++ = *src++;
	}
	*dest = '\0';
	return (result);
}
