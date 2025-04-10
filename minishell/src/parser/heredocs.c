/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/09 17:24:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/10 08:02:16 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "ms_string.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>

/*Building the heredoc in AST*/
t_ast	*create_ast_heredoc(t_ast *left, t_token **tokens)
{
	t_redirect	*redir;
	t_strb		sb;
	char		*line;
	char		*delimiter;

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
	redir->file = ft_strdup(delimiter);
	if (!redir->file)
	{
		free(redir);
		free_ast(left);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		append_strb(&sb, line, ft_strlen(line));
		append_strb(&sb, "\n", 1);
		free(line);
	}
	printf("String: %s\n", sb.str);
	redir->heredoc = sb.str;
	append_redir(left, redir);
	return (left);
}

cc -Wall -Wextra -Werror -lreadline -Iinclude -Ilibft/include src/parser/ast.c src/parser/parser_utils.c src/parser/parser.c src/parser/token.c src/parser/tokenizer_utils.c src/parser/tokenizer.c src/ms_string.c libft/src/ft_calloc.c libft/src/ft_putendl_fd.c libft/src/ft_strdup.c libft/src/ft_strlcat.c libft/src/ft_strlen.c libft/src/ft_substr.c libft/src/ft_bzero.c libft/src/ft_memcpy.c libft/src/ft_putchar_fd.c libft/src/ft_putstr_fd.c tester.c src/parser/quotes.c libft/src/ft_strchrnul.c
