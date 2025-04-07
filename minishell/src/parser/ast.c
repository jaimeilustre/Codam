/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 09:46:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/07 09:31:44 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "ms_string.h"

/*Allocate memory for an Abstract Syntax Tree node*/
t_ast	*allocate_ast_node(t_node_type type)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

/*Create node command*/
t_ast	*create_command_node(char **args)
{
	t_ast	*node;

	node = allocate_ast_node(NODE_COMMAND);
	if (!node)
	{
		free_args(args);
		return (NULL);
	}
	node->args = args;
	return (node);
}

/*Free Abstract Syntax Tree*/
void	free_ast(t_ast *node)
{
	t_redirect	*redir;

	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	while (node->redirect)
	{
		redir = node->redirect;
		node->redirect = redir->next;
		free(redir->file);
		free(redir);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

/*Allocate for redirections in AST*/
t_redirect	*allocate_ast_redir(t_token *token)
{
	t_redirect	*redir;

	redir = ft_calloc(1, sizeof(t_redirect));
	if (!redir)
		return (NULL);
	if (token->type == TOKEN_REDIRECT_IN)
		redir->type = NODE_REDIRECT_IN;
	else if (token->type == TOKEN_REDIRECT_OUT)
		redir->type = NODE_REDIRECT_OUT;
	else if (token->type == TOKEN_APPEND)
		redir->type = NODE_APPEND;
	else if (token->type == TOKEN_HEREDOC)
		redir->type = NODE_HEREDOC;
	else
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

/*Adding later arguments to AST*/
void	add_argument_to_ast(t_ast *left, t_token **tokens)
{
	int	i;

	i = 0;
	while (left->args[i] != NULL)
		i++;
	left->args[i] = ft_strdup((*tokens)->value);
	if (!left->args[i])
	{
		free_args(left->args);
		return ;
	}
	left->args[i + 1] = NULL;
	*tokens = (*tokens)->next;
}
