/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 14:06:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/22 15:09:56 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minishell.h"

/*Parsing subshells (parenthesis)*/
t_ast	*parse_subshell(t_token **tokens, t_alist *env_lst)
{
	t_ast	*subshell;
	t_ast	*node;

	if (*tokens && (*tokens)->type == TOKEN_LEFTPAR)
	{
		*tokens = (*tokens)->next;
		subshell = parse_logical(tokens, env_lst);
		if (!subshell)
			return (NULL);
		if (!*tokens || (*tokens)->type != TOKEN_RIGHTPAR)
			return (free_ast(subshell), NULL);
		*tokens = (*tokens)->next;
		node = allocate_ast_node(NODE_SUBSHELL);
		if (!node)
			return (free_ast(subshell), NULL);
		node->left = subshell;
		return (node);
	}
	return (parse_simple_command(tokens));
}

/*Parsing redirections based on operator precedence*/
t_ast	*parse_redirections(t_token **tokens, t_alist *env_lst)
{
	t_ast	*cmd;

	cmd = parse_subshell(tokens, env_lst);
	if (!cmd)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC
			|| (*tokens)->type == TOKEN_WORD)
		{
			cmd = choose_redir(cmd, tokens, env_lst);
			if (!cmd)
				return (NULL);
		}
		else
			break ;
	}
	return (cmd);
}

/*Parsing pipes based on operator precedence*/
t_ast	*parse_pipes(t_token **tokens, t_alist *env_lst)
{
	t_ast	*left;

	left = parse_redirections(tokens, env_lst);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		left = create_ast_pipe(left, tokens, env_lst);
		if (!left)
			return (NULL);
	}
	return (left);
}

/*Parsing logical operators based on operator precedence*/
t_ast	*parse_logical(t_token **tokens, t_alist *env_lst)
{
	t_ast	*left;

	left = parse_pipes(tokens, env_lst);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		left = create_ast_logical(left, tokens, env_lst);
		if (!left)
			return (NULL);
	}
	return (left);
}

/*Building the Abstract Syntax tree*/
t_ast	*build_ast_tree(t_token *tokens, t_alist *env_lst)
{
	if (tokens == NULL)
	{
		ft_putendl_fd("Syntax error: NULL pointer as first token", STDERR);
		return (NULL);
	}
	else if (!is_valid_token(tokens))
	{
		ft_putstr_fd("Syntax error: near unexpected token `", STDERR);
		ft_putstr_fd(tokens->value, STDERR);
		ft_putendl_fd("'", STDERR);
		return (NULL);
	}
	return (parse_logical(&tokens, env_lst));
}
