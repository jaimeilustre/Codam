/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/09 17:24:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/09 17:25:07 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <readline/readline.h>

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);
	size_t	len3 = ft_strlen(s3);
	char	*res;
	size_t	i = 0, j = 0;

	res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return (NULL);

	// Copy s1
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	// Copy s2
	while (j < len2)
		res[i++] = s2[j++];
	j = 0;
	// Copy s3
	while (j < len3)
		res[i++] = s3[j++];
	res[i] = '\0';
	return (res);
}
#include <stdio.h>

/*Building the heredoc in AST*/
t_ast	*create_ast_heredoc(t_ast *left, t_token **tokens)
{
	t_redirect	*redir;
	char		*line;
	char		*delimiter;
	char		*heredoc_text;

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
		char *tmp = heredoc_text;
		heredoc_text = ft_strjoin3(heredoc_text, line, "0");
		free(tmp);
		free(line);
	}
	printf("String: %s\n", heredoc_text);
	redir->heredoc = heredoc_text;
	append_redir(left, redir);
	return (left);
}