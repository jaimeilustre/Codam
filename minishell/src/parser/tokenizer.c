/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 11:59:08 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/07 15:13:26 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "stdio.h"

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
// int	read_quotes(t_source *src, long start)
// {
// 	char	quote_type;

// 	quote_type = src->buffer[start];
// 	start++;
// 	while (src->curpos < src->bufsize
// 		&& src->buffer[src->curpos] != quote_type)
// 		src->curpos++;
// 	if (src->curpos >= src->bufsize)
// 	{
// 		ft_putendl_fd("Syntax error: unclosed quote", 2);
// 		return (-1);
// 	}
// 	src->curpos++;
// 	while (src->curpos < src->bufsize && !is_space(src->buffer[src->curpos])
// 		&& !is_operator(src->buffer[src->curpos]))
// 		src->curpos++;
// 	return (0);
// }

int	read_quotes(t_source *src, long start)
{
	char	quote_type;

	printf("Read quotes called\n");
	quote_type = src->buffer[start];
	start++;
	while (src->curpos < src->bufsize
		&& src->buffer[src->curpos] != quote_type)
		src->curpos++;
	if (src->curpos >= src->bufsize)
	{
		ft_putendl_fd("Syntax error: unclosed quote", 2);
		return (-1);
	}
	src->curpos++;
	while (src->curpos < src->bufsize && !is_space(src->buffer[src->curpos])
		&& !is_operator(src->buffer[src->curpos]))
		src->curpos++;
	return (0);
}

/*Scans and returns a word token*/
t_token	*return_word_token(t_source *src)
{
	long	start;
	long	length;
	char	*word;
	t_token	*word_token;
	// char	quote_type;

	start = src->curpos - 1;
	if (src->buffer[start] == '\'' || src->buffer[start] == '"')
	{
		if (read_quotes(src, start) == -1)
			return (NULL);
	}
	else
	{
		while (src->curpos < src->bufsize && !is_space(src->buffer[src->curpos])
			&& !is_operator(src->buffer[src->curpos]))
			src->curpos++;
	}
	length = src->curpos - start;
	word = ft_substr(src->buffer, start, length);
	if (!word)
		return (NULL);
	word_token = create_token(TOKEN_WORD, word);
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

	if (check_quotes(src->buffer) == -1)
		return (NULL);
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
		src->curpos--;
		return (return_single_operator_token(c));
	}
	return (return_word_token(src));
}

// #include <stdio.h>

// int main(void)
// {
//     char input[] = "echo 'hello' bye";
//     t_source src;
// 	t_token *token;
//     src.buffer = input;
//     src.bufsize = ft_strlen(input);
//     src.curpos = 0;
//     while ((token = return_next_token(&src)) != NULL)
// 	{
//         if (token->type == TOKEN_EOF)
// 		{
//             free(token);
//             break;
//         }
//         printf("Token type: %d, value: \"%s\"\n", token->type, token->value);
//         free(token->value);
//         free(token);
//     }
//     return (0);
// }
