/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 11:59:06 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/24 11:48:33 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/* Peek at the next character from the input */
char	peek_char(t_source *src)
{
	if (src->curpos >= src->bufsize)
		return ('\0');
	return (src->buffer[src->curpos + 1]);
}

/*Retrieves the next character from the input*/
char	next_char(t_source *src)
{
	if (src->curpos >= src->bufsize)
		return ('\0');
	return (src->buffer[++src->curpos]);
}

/* Check if input is a double operator */
bool	is_double_operator(char c, char d)
{
	return (c == d && (c == '|' || c == '&' || c == '<' || c == '>'));
}

/* Check if input is a single operator */
bool	is_single_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '(' || c == ')');
}

/*Checks if the input contains any whitespaces*/
bool	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
