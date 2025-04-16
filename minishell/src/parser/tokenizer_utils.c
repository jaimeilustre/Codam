/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 11:59:06 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/16 10:23:46 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*Retrives the next character from the input*/
char	next_char(t_source *src)
{
	if (src->curpos >= src->bufsize)
		return ('\0');
	return (src->buffer[src->curpos++]);
}

/*Checks if the input contains an operator*/
bool	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == '(' || c == ')');
}

/*Checks if the input contains any whitespaces*/
bool	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
