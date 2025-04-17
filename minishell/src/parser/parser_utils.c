/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 12:20:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/17 15:08:04 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "parser.h"
#include "ms_string.h"

/*Count args for args array*/
int	arg_count(t_token *tokens)
{
	int		count;

	count = 0;
	while (is_valid_token(tokens))
	{
		if (tokens->type == TOKEN_WORD)
			++count;
		tokens = tokens->next;
	}
	return (count);
}

/*Free tokens after use*/
void	free_token_list(t_token **head)
{
	t_token	*temp;

	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free_token(temp);
	}
	*head = NULL;
}

/*Appending redirection to ast*/
void	append_redir(t_ast *left, t_redirect *redir)
{
	t_redirect	*temp;

	if (!left->redirect)
		left->redirect = redir;
	else
	{
		temp = left->redirect;
		while (temp->next)
			temp = temp->next;
		temp->next = redir;
	}
}

/*Checks if after operator a valid token is present*/
bool	is_valid_token(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_WORD
		|| token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_LEFTPAR)
		return (true);
	return (false);
}
