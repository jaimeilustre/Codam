/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/09 17:24:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/18 11:32:21 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>

#include "libft.h"
#include "exec.h"
#include "list.h"
#include "parser.h"
#include "ms_signals.h"
#include "ms_string.h"
#include "ms_error.h"

/*Handles delimiter or quoted delimiter*/
static int	check_delimiter(t_redirect *redir, t_token *tokens, int *in_quotes)
{
	char	*unquoted_delimiter;

	*in_quotes = tokens->quoted;
	if (tokens->quoted)
	{
		unquoted_delimiter = remove_quotes(tokens);
		if (!unquoted_delimiter)
			return (0);
		redir->file = unquoted_delimiter;
	}
	else
		redir->file = ft_strdup(tokens->value);
	return (redir->file != NULL);
}

/*Handles variable expansion in heredoc input*/
static int	heredoc_exp(t_strb *sb, t_cstr line, int quoted, t_alist *env_lst)
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

static int	end_of_heredoc(char *line, char *delim)
{
	if (line == NULL)
	{
		ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delim, 2);
		ft_putendl_fd("\')", 2);
		return (1);
	}
	return (ft_strcmp(line, delim) == 0);
}

/*Handles regular line heredoc input*/
static int	heredoc_input(t_redirect *redir, int quoted, t_alist *env_lst)
{
	t_strb	sb;
	char	*line;

	if (!trap_sigint_heredoc() || !init_strb(&sb, 512))
		return (ms_error(PERROR, NULL, NULL), 0);
	while (1)
	{
		g_signo = 0;
		line = readline("> ");
		if (g_signo == SIGINT)
			return (free(line), free_strb(&sb), 0);
		else if (end_of_heredoc(line, redir->file))
			break ;
		else if (!heredoc_exp(&sb, line, quoted, env_lst))
			return (free(line), free_strb(&sb), 0);
		free(line);
	}
	free(line);
	free(redir->file);
	shrink_strb(&sb);
	redir->file = sb.str;
	return (1);
}

/*Building the heredoc in AST*/
t_ast	*create_ast_heredoc(t_ast *left, t_token **tokens, t_alist *env_lst)
{
	t_redirect	*redir;
	int			in_quotes;

	redir = allocate_ast_redir(*tokens);
	if (!redir)
		return (free_ast(left), NULL);
	append_redir(left, redir);
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
	{
		ft_putendl_fd("Syntax error: near unexpected token `newline'", 2);
		return (free_ast(left), NULL);
	}
	else if (check_delimiter(redir, *tokens, &in_quotes))
	{
		*tokens = (*tokens)->next;
		if (heredoc_input(redir, in_quotes, env_lst))
			return (left);
	}
	return (free_ast(left), NULL);
}
