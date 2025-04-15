/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 14:06:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/15 14:12:25 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*Parsing redirections based on operator precedence*/
t_ast	*parse_redirections(t_token **tokens, t_alist *env_lst)
{
	t_ast	*cmd;

	cmd = parse_simple_command(tokens);
	if (!cmd)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_APPEND)
		{
			cmd = create_ast_redir(cmd, tokens);
			if (!cmd)
				return (NULL);
		}
		else if ((*tokens)->type == TOKEN_HEREDOC)
		{
			cmd = create_ast_heredoc(cmd, tokens, env_lst);
			if (!cmd)
				return (NULL);
		}
		else if ((*tokens)->type == TOKEN_WORD)
			add_argument_to_ast(cmd, tokens);
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
t_ast	*build_ast_tree(t_token **tokens, t_alist *env_lst)
{
	return (parse_logical(tokens, env_lst));
}
