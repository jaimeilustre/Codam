/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 12:20:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/03/20 12:42:23 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "ms_string.h"

/*Count args for args array*/
int	arg_count(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens && tokens->type == TOKEN_WORD)
	{
		i++;
		tokens = tokens->next;
	}
	if (i == 0)
		return (0);
	return (i);
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
