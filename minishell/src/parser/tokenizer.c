/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 11:59:08 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/11 11:39:22 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*Scans and returns a word token*/
t_token	*return_word_token(t_source *src)
{
	long	start;
	long	length;
	char	*word;
	t_token	*word_token;
	int		quoted;
	
	quoted = 0;
	start = src->curpos - 1;
	src->curpos = start;
	while (src->curpos < src->bufsize)
	{
		if (src->buffer[src->curpos] == '\'' || src->buffer[src->curpos] == '"')
		{
			read_quotes(src, src->curpos);
			quoted = 1;
		}
		else if (is_space(src->buffer[src->curpos]))
			break ;
		else if (is_operator(src->buffer[src->curpos]))
			break ;
		else
			src->curpos++;
	}
	length = src->curpos - start;
	word = ft_substr(src->buffer, start, length);
	if (!word)
		return (NULL);
	word_token = create_token(TOKEN_WORD, word);
	word_token->quoted = quoted;
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
	free(operator);
	return (NULL);
}

/*Return double operator token*/
t_token	*return_double_operator_token(t_source *src, char c)
{
	char	*operator;
	char	next;

	next = next_char(src);
	if ((c == '>' || c == '<') && next == c)
	{
		operator = ft_strdup((char []){c, next, '\0'});
		if (!operator)
			return (NULL);
		if (c == '>')
			return (create_token(TOKEN_APPEND, operator));
		else
			return (create_token(TOKEN_HEREDOC, operator));
	}
	if ((c == '&' && next == '&') || (c == '|' && next == '|'))
	{
		operator = ft_strdup((char []){c, next, '\0'});
		if (!operator)
			return (NULL);
		if (c == '&')
			return (create_token(TOKEN_AND, operator));
		else
			return (create_token(TOKEN_OR, operator));
	}
	return (NULL);
}

/*Returns the next token from the input, including operators and EOF*/
t_token	*return_next_token(t_source *src)
{
	char	c;
	t_token	*token;

	c = next_char(src);
	while (c && is_space(c))
		c = next_char(src);
	if (c == '\0')
		return (allocate_token(TOKEN_EOF, NULL));
	if (is_operator(c))
	{
		token = return_double_operator_token(src, c);
		if (token != NULL)
			return (token);
		if (src->curpos < src->bufsize)
			src->curpos--;
		return (return_single_operator_token(c));
	}
	return (return_word_token(src));
}
