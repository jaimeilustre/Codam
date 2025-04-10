/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 09:55:13 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/10 07:57:14 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

/*Printing the Abstract Syntax Tree*/
void	print_ast(t_ast *node, int indent, char *prefix)
{
	if (!node)
		return ;
	printf("%s", prefix);
	if (node->type == NODE_COMMAND)
	{
		printf("COMMAND: ");
		if (node->args)
		{
			int i = 0;
			while (node->args[i] != NULL)
			{
				printf("%s ", node->args[i]);
				i++;
			}
		}
		printf("\n");
		t_redirect *redir = node->redirect;
		while (redir != NULL)
		{
			if (redir->type == NODE_REDIRECT_IN)
				printf("%s    ├── REDIR_IN: %s\n", prefix, redir->file);
			else if (redir->type == NODE_REDIRECT_OUT)
				printf("%s    ├── REDIR_OUT: %s\n", prefix, redir->file);
			else if (redir->type == NODE_APPEND)
				printf("%s    ├── APPEND: %s\n", prefix, redir->file);
			else if (redir->type == NODE_HEREDOC)
				printf("%s    ├── HEREDOC: %s\n", prefix, redir->file);
			redir = redir->next;
		}
	}
	else if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_AND)
		printf("AND\n");
	else if (node->type == NODE_OR)
		printf("OR\n");
	else
		printf("UNKNOWN\n");
	char left_prefix[256], right_prefix[256];
	snprintf(left_prefix, sizeof(left_prefix), "%s├── ", prefix);
	snprintf(right_prefix, sizeof(right_prefix), "%s└── ", prefix);
	print_ast(node->left, indent + 1, left_prefix);
	print_ast(node->right, indent + 1, right_prefix);
}

/* ADD CHECK FOR VALID FILE AFTER REDIRECTION AND EXCLUDE OPERATORS AS FILES*/
int	main(void)
{
	// char		*input_pipes = "ls -l | grep txt |  wc -l";
	// char		*input_quotes = "echo 'hello'bye";
	char		*input_redir = "cat << EOF";
	// char		*input_logical = "echo 'Hello World' | ls && ls || echo 'World'";
	t_source	src;
	t_token		*token;
	t_token		*token_list = NULL;
	t_ast		*ast;
	t_token		*last;
	t_token		*backup;

	src.buffer = input_redir;
	src.bufsize = ft_strlen(input_redir);
	src.curpos = 0;
	while ((token = return_next_token(&src)) != NULL)
	{
		if (token->type == TOKEN_EOF)
		{
			free_token(token);
			break ;
		}
		// printf("New token created: %s (Type: %d)\n", token->value, token->type);
		if (!token_list)
		{
			token_list = token;
			// printf("token_list initialized with token: %s\n", token->value);
		}
		else
		{
			last->next = token;
			// printf("Added token to list: %s\n", token->value);
		}
		last = token;
	}
	// printf("Before AST creation: token_list at %p\n", token_list);
	backup = token_list;
	ast = build_ast_tree(&token_list);
	// printf("After AST creation: token_list at %p\n", token_list);
	print_ast(ast, 0, "");
	free_token_list(&backup);
	free_ast(ast);
	return (0);
}

// i = 0;
// 	while (args[i])
// 	{
// 		printf("%s\n", args[i]);
// 		i++;
// 	}

// if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
// {
// 	free(node);
// 	free_ast(left);
// 	return (NULL);
// }

// #include <stdio.h>

// int main(void)
// {
//     char input[] = "cat < hi < helo dafs > bye";
//     t_source src;
// 	t_token *token;
//     src.buffer = input;
//     src.bufsize = ft_strlen(input);
//     src.curpos = 0;
//     while ((token = return_next_token(&src)) != NULL)
// 	{
//         if (token->type == TOKEN_EOF)
// 		{
//             free(token);
//             break;
//         }
//         printf("Token type: %d, value: \"%s\"\n", token->type, token->value);
//         free(token->value);
//         free(token);
//     }
//     return (0);
// }