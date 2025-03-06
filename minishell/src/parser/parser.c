/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/03/06 17:06:52 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "ms_string.h"
#include <stdio.h>

/*Parse simple command and return node command*/
t_ast	*parse_simple_command(t_token **tokens)
{
	char	**args;
	int		i;

	args = malloc ((arg_count(*tokens) + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
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
	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (create_command_node(args));
}

/*Building the pipe in AST*/
t_ast	*create_ast_pipe(t_ast *left, t_token **tokens)
{
	t_ast	*node;

	node = allocate_ast_node(NODE_PIPE);
	if (!node)
	{
		free_ast(left);
		return (NULL);
	}
	node->left = left;
	*tokens = (*tokens)->next;
	node->right = build_ast_tree(tokens);
	if (!node->right)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

/*Building the redirection in AST*/
t_ast	*create_ast_redir(t_ast *left, t_token **tokens)
{
	t_redirect	*redir = NULL;

	if ((*tokens)->type == TOKEN_REDIRECT_IN)
		redir = allocate_ast_redir(NODE_REDIRECT_IN);
	else if ((*tokens)->type == TOKEN_REDIRECT_OUT)
		redir = allocate_ast_redir(NODE_REDIRECT_OUT);
	if (!redir)
	{
		free_ast(left);
		return (NULL);
	}
	
}

/*Building the Abstract Syntax tree*/
t_ast	*build_ast_tree(t_token **tokens)
{
	t_ast	*left;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_simple_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN_PIPE)
			left = create_ast_pipe(left, tokens);
		// else if ((*tokens)->type == TOKEN_REDIRECT_IN
		// 	|| (*tokens)->type == TOKEN_REDIRECT_OUT)
			
		else
			break ;
	}
	return (left);
}
