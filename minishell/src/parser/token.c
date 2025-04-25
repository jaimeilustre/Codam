/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 09:43:37 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/25 08:47:42 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "exec.h"
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

t_token	*create_tokens(t_str cmd, int *error)
{
	t_source	src;
	t_token		*first_token;
	t_token		*last_token;

	*error = 0;
	if (check_quotes(cmd) == -1)
	{
		*error = 1;
		return (NULL);
	}
	src = (t_source){cmd, ft_strlen(cmd), 0};
	first_token = return_next_token(&src);
	last_token = first_token;
	while (last_token != NULL)
	{
		if (last_token->type == TOKEN_EOF)
			break ;
		last_token->next = return_next_token(&src);
		last_token = last_token->next;
	}
	return (first_token);
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
