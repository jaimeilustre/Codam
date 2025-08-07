/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 14:06:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/28 12:07:46 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*Parsing subshells (parenthesis)*/
t_ast	*parse_subshell(t_token **tokens, t_alist *env_lst)
{
	if (*tokens && (*tokens)->type == TOKEN_LPAR)
		return (create_ast_subshell(tokens, env_lst));
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
			|| (*tokens)->type == TOKEN_WRD)
		{
			cmd = choose_redir(cmd, tokens, env_lst);
			if (!cmd)
				return (NULL);
		}
		else if ((*tokens)->type == TOKEN_LPAR)
			return (syntax_error(SYN_SUBSHELL_AFTER_CMD, NULL)
				, free_ast(cmd), NULL);
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
		left = create_ast_logic(left, tokens, env_lst);
		if (!left)
			return (NULL);
	}
	return (left);
}

/*Building the Abstract Syntax tree*/
t_ast	*build_ast_tree(t_token *tokens, t_alist *env_lst)
{
	if (!check_opening_parenthesis(tokens))
		return (NULL);
	if (tokens == NULL)
		return (syntax_error(SYN_NULL_POINTER, NULL), NULL);
	else if (!is_valid_token(tokens))
		return (syntax_error(SYN_UNEXPEC_TOKEN, tokens->value), NULL);
	return (parse_logical(&tokens, env_lst));
}
