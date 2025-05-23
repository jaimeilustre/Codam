/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 12:20:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/25 10:24:31 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "ms_string.h"
#include "parser.h"

/*Count args for args array*/
int	arg_count(t_token *tokens)
{
	int		count;

	count = 0;
	while (is_valid_token(tokens))
	{
		if (tokens->type == TOKEN_WRD)
			++count;
		tokens = tokens->next;
	}
	return (count);
}

/*Free tokens after use*/
void	free_token_list(t_token **head)
{
	t_token	*tmp;
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free_token(tmp);
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

/*Determine which redirection function to call*/
t_ast	*choose_redir(t_ast *cmd, t_token **tokens, t_alist *env_lst)
{
	if ((*tokens)->type == TOKEN_REDIRECT_IN
		|| (*tokens)->type == TOKEN_REDIRECT_OUT
		|| (*tokens)->type == TOKEN_APPEND)
		cmd = create_ast_redir(cmd, tokens);
	else if ((*tokens)->type == TOKEN_HEREDOC)
		cmd = create_ast_hdoc(cmd, tokens, env_lst);
	else if ((*tokens)->type == TOKEN_WRD)
	{
		if (add_argument_to_ast(cmd, tokens) == -1)
			return (NULL);
	}
	return (cmd);
}

/*Checks if after operator a valid token is present*/
bool	is_valid_token(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_WRD
		|| token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_LPAR)
		return (true);
	return (false);
}
