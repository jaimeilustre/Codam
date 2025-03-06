/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 09:46:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/03/06 09:42:25 by jilustre      ########   odam.nl         */
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
	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

/*Allocate for redirection in AST*/
t_redirect	*allocate_ast_redir(t_node_type type)
{
	t_redirect	*redir;

	redir = ft_calloc(1, sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	return (redir);
}
