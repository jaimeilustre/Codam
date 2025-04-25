/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 11:59:08 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/25 10:21:09 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "parser.h"

/*Reads word for word token*/
static void	read_word(t_source *src)
{
	while (src->curpos < src->bufsize)
	{
		if (src->buffer[src->curpos] == '\'' || src->buffer[src->curpos] == '"')
			read_quotes(src, src->curpos);
		else if (is_space(src->buffer[src->curpos])
			|| is_double_operator(src->buffer[src->curpos], peek_char(src))
			|| is_single_operator(src->buffer[src->curpos]))
			break ;
		else
			src->curpos++;
	}
}

/*Scans and returns a word token*/
t_token	*return_word_token(t_source *src)
{
	long	start;
	char	*word;
	t_token	*word_token;

	start = src->curpos;
	src->curpos = start;
	read_word(src);
	word = ft_substr(src->buffer, start, src->curpos - start);
	if (!word)
		return (NULL);
	word_token = create_token(TOKEN_WRD, word);
	return (word_token);
}

/*Return single operator token*/
t_token	*return_single_operator_token(char c)
{
	char	*operator;

	operator = ft_strdup((char []){c, '\0'});
	if (!operator)
		return (NULL);
	if (c == '>')
		return (create_token(TOKEN_REDIRECT_OUT, operator));
	if (c == '<')
		return (create_token(TOKEN_REDIRECT_IN, operator));
	if (c == '|')
		return (create_token(TOKEN_PIPE, operator));
	if (c == '(')
		return (create_token(TOKEN_LPAR, operator));
	if (c == ')')
		return (create_token(TOKEN_RPAR, operator));
	free(operator);
	return (NULL);
}

/*Return double operator token*/
t_token	*return_double_operator_token(t_source *src, char c)
{
	char	*operator;
	char	next;

	next = next_char(src);
	src->curpos++;
	if ((c == '>' || c == '<') && next == c)
	{
		operator = ft_strdup((char []){c, next, '\0'});
		if (!operator)
			return (NULL);
		if (c == '>')
			return (create_token(TOKEN_APPEND, operator));
		return (create_token(TOKEN_HEREDOC, operator));
	}
	if ((c == '&' && next == '&') || (c == '|' && next == '|'))
	{
		operator = ft_strdup((char []){c, next, '\0'});
		if (!operator)
			return (NULL);
		if (c == '&')
			return (create_token(TOKEN_AND, operator));
		return (create_token(TOKEN_OR, operator));
	}
	return (NULL);
}

/*Returns the next token from the input, including operators and EOF*/
t_token	*return_next_token(t_source *src)
{
	char	c;

	c = src->buffer[src->curpos];
	while (c && is_space(c))
		c = next_char(src);
	if (c == '\0')
		return (allocate_token(TOKEN_EOF, NULL));
	if (is_double_operator(c, peek_char(src)))
		return (return_double_operator_token(src, c));
	else if (is_single_operator(c))
	{
		src->curpos++;
		return (return_single_operator_token(c));
	}
	return (return_word_token(src));
}
