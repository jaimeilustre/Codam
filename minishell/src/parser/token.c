/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 09:43:37 by jilustre      #+#    #+#                 */
/*   Updated: 2025/03/03 10:42:30 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*Create a new token*/
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = allocate_token(type, value);
	if (!token)
		return (free(value), NULL);
	return (token);
}

/*Allocate memory for a new token*/
t_token	*allocate_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

/*Free the memory used by the token struct*/
void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}
