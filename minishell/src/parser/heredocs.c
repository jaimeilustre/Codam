/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/09 17:24:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/12 10:48:12 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "ms_string.h"

#include "exec.h"
#include "list.h"

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdio.h>

char	*remove_quotes(const char *str)
{
	const char	*src = str;
	char		*result;
	char		*dst;
	char		quote = 0;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	dst = result;
	while (*src)
	{
		if (!quote && (*src == '\'' || *src == '"'))
			quote = *src++;
		else if (quote && *src == quote)
		{
			quote = 0;
			src++;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (result);
}

/*Building the heredoc in AST*/
t_ast	*create_ast_heredoc(t_ast *left, t_token **tokens, t_alist *env_lst)
{
	t_redirect	*redir;
	t_strb		sb;
	char		*line;
	char		*delimiter;
	t_cstr		ptr;
	int			in_quotes;
	char		*unquoted_delimiter;

	redir = allocate_ast_redir(*tokens);
	if (!redir)
	{
		free_ast(left);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
	{
		ft_putendl_fd("Heredoc must be followed by a delimiter", 2);
		free(redir);
		free_ast(left);
		return (NULL);
	}
	delimiter = ((*tokens)->value);
	if ((*tokens)->quoted)
	{
		unquoted_delimiter = remove_quotes(delimiter);
		if (!unquoted_delimiter)
			return (free(unquoted_delimiter), NULL);
		free(delimiter);
		delimiter = unquoted_delimiter;
		// free(unquoted_delimiter);
	}
	redir->file = ft_strdup(delimiter);
	if (!redir->file)
	{
		free(redir);
		free_ast(left);
		return (NULL);
	}
	in_quotes = ((*tokens)->quoted);
	*tokens = (*tokens)->next;
	if (!init_strb(&sb, 512))
	{
		free(redir->file);
		free(redir);
		free_ast(left);
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{			
			free(line);
			break ;
		}
		if (in_quotes)
			append_strb(&sb, line, ft_strlen(line));
		else
		{
			ptr = line;
			while (*ptr)
			{
				if (*ptr == '$')
				{
					if (!expand_variable(&sb, &ptr, env_lst))
					{
						free(line);
						free(redir);
						free_ast(left);
						return (NULL);
					}
				}
				else
					append_strb(&sb, ptr, 1);
				ptr++;
			}
		}
		append_strb(&sb, "\n", 1);
		free(line);
	}
	free(redir->file);
	free(unquoted_delimiter);
	redir->file = sb.str;
	append_redir(left, redir);
	printf("String:\n%s", redir->file);
	return (left);
}
