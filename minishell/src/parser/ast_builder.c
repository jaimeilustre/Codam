/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast_builder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/25 08:23:06 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"

#include "list.h"
#include "ms_string.h"
#include "parser.h"

/*Parse simple command and return node command*/
t_ast	*parse_simple_command(t_token **tokens)
{
	char	**args;
	int		i;

	args = malloc((arg_count(*tokens) + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (*tokens && ((*tokens)->type == TOKEN_WRD))
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
	if (*tokens && (*tokens)->type == TOKEN_LPAR)
		return (syntax_error(SYN_SUBSHELL_AFTER_CMD, NULL)
			, free_args(args), NULL);
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
	if (!is_valid_token(*tokens))
		return (syntax_error(SYN_EOF, NULL), free(node), free_ast(left), NULL);
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
	if (!(*tokens) || (*tokens)->type != TOKEN_WRD)
		return (syntax_error(SYN_EOF, NULL), free(redir), free_ast(left), NULL);
	redir->file = ft_strdup((*tokens)->value);
	if (!redir->file)
		return (free(redir), free_ast(left), NULL);
	*tokens = (*tokens)->next;
	append_redir(left, redir);
	return (left);
}

/*Building the logical operator in AST*/
t_ast	*create_ast_logic(t_ast *left, t_token **tokens, t_alist *env_lst)
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
	if (!is_valid_token(*tokens))
		return (syntax_error(SYN_EOF, NULL), free(node), free_ast(left), NULL);
	node->right = parse_pipes(tokens, env_lst);
	if (!node->right)
		return (free_ast(node), NULL);
	return (node);
}

/*Building the subshell in AST*/
t_ast	*create_ast_subshell(t_token **tokens, t_alist *env_lst)
{
	t_ast	*subshell;
	t_ast	*node;

	*tokens = (*tokens)->next;
	if (!*tokens)
		return (NULL);
	if (((*tokens)->type != TOKEN_WRD && (*tokens)->type != TOKEN_LPAR))
		return (syntax_error(SYN_UNEXPEC_TOKEN, (*tokens)->value), NULL);
	if ((*tokens)->type == TOKEN_RPAR)
		return (syntax_error(SYN_EMPTY_SUBSHELL, NULL), NULL);
	subshell = parse_logical(tokens, env_lst);
	if (!subshell)
		return (NULL);
	if ((*tokens)->type != TOKEN_RPAR)
		return (syntax_error(SYN_CLOSE_PAR, NULL), free_ast(subshell), NULL);
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type != TOKEN_PIPE && (*tokens)->type != TOKEN_AND
		&& (*tokens)->type != TOKEN_OR && (*tokens)->type != TOKEN_RPAR
		&& (*tokens)->type != TOKEN_EOF)
		return (syntax_error(SYN_AFT_SUBSHELL, NULL), free_ast(subshell), NULL);
	node = allocate_ast_node(NODE_SUBSHELL);
	if (!node)
		return (free_ast(subshell), NULL);
	node->left = subshell;
	return (node);
}
