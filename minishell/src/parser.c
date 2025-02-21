/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/21 08:22:36 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"

/*Tokenization*/

/*Retrives the next character from the input*/
char next_char(t_source *src)
{
	if (src->curpos >= src->bufsize)
		return ('\0');
	return (src->buffer[src->curpos++]);
}

/*Checks if the input contains an operator*/
bool is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

/*Checks if the input contains any whitespaces*/
bool is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*Free the memory used by the token struct*/
void free_token(t_token *tok)
{
	if (tok->value)
		free(tok->value);
	free(tok);
}

/*Allocate memory for a new token*/
t_token	*create_token(t_token_type type, char *value)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

/*Scans and returns a word token*/
t_token *scan_word_token(t_source *src)
{
    long	start;
	long	length;
	char	*word;
	long	i;

	start = src->curpos - 1;
    while (src->curpos < src->bufsize &&
           !is_space(src->buffer[src->curpos]) &&
           !is_operator(src->buffer[src->curpos])) {
        src->curpos++;
    }
    length = src->curpos - start;
    word = malloc(length + 1);
    if (!word)
		return NULL;
	i = 0;
    while (i < length)
	{
        word[i] = src->buffer[start + i];
		i++;
	}
    word[length] = '\0';
    return create_token(TOKEN_WORD, word);
}

/*Returns the next token from the input, including operators and EOF*/
t_token *get_next_token(t_source *src)
{
	char	c;
	char	*operator;
	char	next;
    
    while ((c = next_char(src)) && is_space(c))
        ;
    if (c == '\0')
        return create_token(TOKEN_EOF, NULL);
    if (is_operator(c)) 
	{
        operator = malloc(3);
        if (!operator)
            return (free(operator), NULL);
        operator[0] = c;
        operator[1] = '\0';
        operator[2] = '\0';
		next = next_char(src);
		if ((c == '&' && next == '<') || (c == '|' && next == '|'))
		{
            operator[1] = next;
            if (c == '&')
            	return create_token(TOKEN_AND, operator);
            else
                return create_token(TOKEN_OR, operator);   
        }
        if ((c == '>' || c == '<') && next == c)
		{
            operator[1] = next;
            if (c == '>')
                return create_token(TOKEN_APPEND, operator);
            else
                return create_token(TOKEN_HEREDOC, operator);
        }
		src->curpos--;
        if (c == '>')
            return create_token(TOKEN_REDIRECT_OUT, operator);
        if (c == '<')
            return create_token(TOKEN_REDIRECT_IN, operator);
		if (c == '|')
			return create_token(TOKEN_PIPE, operator);
		if (c == '&')
			return create_token(TOKEN_AMPERSAND, operator);
        // return create_token(TOKEN_PIPE, operator);
    }
    return scan_word_token(src);
}

#include <stdio.h>
#include <string.h>
#include "libft.h"

int main(void)
{
    char input[] = "ls -la | grep txt > out.txt";
    
    t_source src;
	t_token *token;
	
    src.buffer = input;
    src.bufsize = ft_strlen(input);
    src.curpos = 0;
    while ((token = get_next_token(&src)) != NULL) {
        if (token->type == TOKEN_EOF) {
            free(token);
            break;
        }
        printf("Token type: %d, value: \"%s\"\n", token->type, token->value);
        free(token->value);
        free(token);
    }
    return (0);
}

/*Creating the Abstract Syntax Tree*/



