/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_paren_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 15:18:19 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/24 17:17:35 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "exec.h"
#include "ms_error.h"
#include "minishell.h"

/*Checking for unclosed quotes before tokenization*/
int	check_quotes(const char *input)
{
	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			input = ft_strchrnul(input + 1, *input);
			if (*input == '\0')
				return (syntax_error(SYN_UNCLOSED_QUOTE, NULL), -1);
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

/*Checks for opening parenthesis*/
bool	check_opening_parenthesis(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	while (current)
	{
		if (current->type == TOKEN_LPAR)
			count++;
		if (current->type == TOKEN_RPAR)
			count--;
		if (count < 0)
			return (syntax_error(SYN_EXPEC_OPEN_PAR, NULL), false);
		current = current->next;
	}
	return (true);
}
