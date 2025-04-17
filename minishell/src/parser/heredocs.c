/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/09 17:24:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/17 16:50:23 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "ms_string.h"
#include "exec.h"
#include "list.h"
#include <stdlib.h>
#include <readline/readline.h>

/*Initializes heredoc for AST*/
t_redirect	*initialize_heredoc(t_ast *left, t_token **tokens)
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
		ft_putendl_fd("Syntax error: near unexpected token `newline'", 2);
		free(redir);
		free_ast(left);
		return (NULL);
	}
	return (redir);
}

/*Handles delimiter or quoted delimiter*/
int	check_delimiter(t_redirect *redir, t_token *tokens, int *in_quotes)
{
	char	*unquoted_delimiter;

	*in_quotes = tokens->quoted;
	if (tokens->quoted)
	{
		unquoted_delimiter = remove_quotes(tokens);
		if (!unquoted_delimiter)
			return (0);
		redir->file = ft_strdup(unquoted_delimiter);
		free(unquoted_delimiter);
	}
	else
		redir->file = ft_strdup(tokens->value);
	return (redir->file != NULL);
}

/*Handles variable expansion in heredoc input*/
int	heredoc_exp(t_strb *sb, const char *line, int quoted, t_alist *env_lst)
{
	t_cstr	ptr;

	ptr = line;
	if (quoted)
		return (append_strb(sb, line, ft_strlen(line))
			&& append_strb(sb, "\n", 1));
	while (*ptr)
	{
		ptr = ft_strchrnul(ptr, '$');
		if (!append_strb(sb, line, ptr - line)
			|| (*ptr == '$' && !expand_variable(sb, &ptr, env_lst)))
			return (0);
		line = ptr + 1;
	}
	return (append_strb(sb, "\n", 1));
}

/*Handles regular line heredoc input*/
int	heredoc_input(t_redirect *redir, int quoted, t_alist *env_lst)
{
	t_strb	sb;
	char	*line;

	if (!init_strb(&sb, 512))
		return (0);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		if (!heredoc_exp(&sb, line, quoted, env_lst))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	free(redir->file);
	redir->file = sb.str;
	return (1);
}

/*Building the heredoc in AST*/
t_ast	*create_ast_heredoc(t_ast *left, t_token **tokens, t_alist *env_lst)
{
	t_redirect	*redir;
	int			in_quotes;

	redir = initialize_heredoc(left, tokens);
	if (!redir)
		return (NULL);
	if (!check_delimiter(redir, *tokens, &in_quotes))
	{
		free(redir);
		free_ast(left);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	if (!heredoc_input(redir, in_quotes, env_lst))
	{
		free(redir);
		free_ast(left);
		return (NULL);
	}
	append_redir(left, redir);
	return (left);
}
