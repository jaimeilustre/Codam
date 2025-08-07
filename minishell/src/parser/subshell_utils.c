/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subshell_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 12:15:07 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/28 12:17:13 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*subshell_redir(t_ast *node, t_token **tokens, t_alist *env_lst)
{
	while (*tokens && ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC))
	{
		node = choose_redir(node, tokens, env_lst);
		if (!node)
			return (NULL);
	}
	return (node);
}
