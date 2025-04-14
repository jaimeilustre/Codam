/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/14 10:18:56 by jilustre      ########   odam.nl         */
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
	{
		free_ast(left);
		return (NULL);
	}
	node->left = left;
	*tokens = (*tokens)->next;
	if (!is_valid_next_token(*tokens))
	{
		ft_putendl_fd("Pipe must be followed by an operator or command", 2);
		free(node);
		free_ast(left);
		return (NULL);
	}
	node->right = build_ast_tree(tokens, env_lst);
	if (!node->right)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

/*Building the redirections in AST*/
t_ast	*create_ast_redir(t_ast *left, t_token **tokens)
{
	t_redirect	*redir;

	redir = allocate_ast_redir(*tokens);
	if (!redir)
	{
		free_ast(left);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
	{
		ft_putendl_fd("Redirection must be followed by a file", 2);
		free(redir);
		free_ast(left);
		return (NULL);
	}
	redir->file = ft_strdup((*tokens)->value);
	if (!redir->file)
	{
		free(redir);
		free_ast(left);
		return (NULL);
	}
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
	{
		free_ast(left);
		return (NULL);
	}
	node->left = left;
	*tokens = (*tokens)->next;
	node->right = build_ast_tree(tokens, env_lst);
	if (!node->right)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

/*Building the Abstract Syntax tree*/
t_ast	*build_ast_tree(t_token **tokens, t_alist *env_lst)
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
			left = create_ast_pipe(left, tokens, env_lst);
		else if ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_APPEND)
			left = create_ast_redir(left, tokens);
		else if ((*tokens)->type == TOKEN_HEREDOC)
			left = create_ast_heredoc(left, tokens, env_lst);
		else if ((*tokens)->type == TOKEN_WORD)
			add_argument_to_ast(left, tokens);
		else if ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR)
			left = create_ast_logical(left, tokens, env_lst);
		else
			break ;
		if (!left)
			return (NULL);
	}
	return (left);
}
