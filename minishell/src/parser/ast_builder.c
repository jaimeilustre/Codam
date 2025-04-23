/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast_builder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/18 10:54:01 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "ms_string.h"
#include "list.h"

/*Parse simple command and return node command*/
t_ast	*parse_simple_command(t_token **tokens)
{
	char	**args;
	int		i;

	args = malloc((arg_count(*tokens) + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (*tokens && ((*tokens)->type == TOKEN_WORD))
	{
		args[i] = ft_strdup((*tokens)->value);
		if (!args[i])
		{
			free_args(args);
			return (NULL);
		}
		i++;
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (create_command_node(args));
}

/*Building the pipe in AST*/
t_ast	*create_ast_pipe(t_ast *left, t_token **tokens, t_alist *env_lst)
{
	t_ast	*node;

	node = allocate_ast_node(NODE_PIPE);
	if (!node)
		return (free_ast(left), NULL);
	node->left = left;
	*tokens = (*tokens)->next;
	if (!(*tokens) || !is_valid_token(*tokens))
	{
		ft_putendl_fd("Syntax error: unexpected end of file", 2);
		free(node);
		free_ast(left);
		return (NULL);
	}
	node->right = parse_redirections(tokens, env_lst);
	if (!node->right)
		return (free_ast(node), NULL);
	return (node);
}

/*Building the redirections in AST*/
t_ast	*create_ast_redir(t_ast *left, t_token **tokens)
{
	t_redirect	*redir;

	redir = allocate_ast_redir(*tokens);
	if (!redir)
		return (free_ast(left), NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
	{
		ft_putendl_fd("Syntax error: unexpected end of file", 2);
		free(redir);
		free_ast(left);
		return (NULL);
	}
	redir->file = ft_strdup((*tokens)->value);
	if (!redir->file)
		return (free(redir), free_ast(left), NULL);
	*tokens = (*tokens)->next;
	append_redir(left, redir);
	return (left);
}

/*Building the logical operator in AST*/
t_ast	*create_ast_logical(t_ast *left, t_token **tokens, t_alist *env_lst)
{
	t_ast	*node;

	node = NULL;
	if ((*tokens)->type == TOKEN_AND)
		node = allocate_ast_node(NODE_AND);
	else if ((*tokens)->type == TOKEN_OR)
		node = allocate_ast_node(NODE_OR);
	if (!node)
		return (free_ast(left), NULL);
	node->left = left;
	*tokens = (*tokens)->next;
	if (!(*tokens) || !is_valid_token(*tokens))
	{
		ft_putendl_fd("Syntax error: unexpected end of file", 2);
		free(node);
		free_ast(left);
		return (NULL);
	}
	node->right = parse_pipes(tokens, env_lst);
	if (!node->right)
		return (free_ast(node), NULL);
	return (node);
}
