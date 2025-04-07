/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 12:20:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/07 12:40:17 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "ms_string.h"

#include <stdio.h>

/*Count args for args array*/
int	arg_count(t_token *tokens)
{
	int		count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		else if (tokens->type == TOKEN_REDIRECT_IN
			|| tokens->type == TOKEN_REDIRECT_OUT
			|| tokens->type == TOKEN_APPEND
			|| tokens->type == TOKEN_HEREDOC)
			tokens = tokens->next;
		if (tokens != NULL)
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
