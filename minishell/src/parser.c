/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/14 16:38:58 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"

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
	return (c == '|' || c == '>' || c == '<' || c == '>>' || c == '<<');
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

t_token *input_to_token(t_source *src)
{
	
}

