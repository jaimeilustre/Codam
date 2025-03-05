/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 09:55:13 by jilustre      #+#    #+#                 */
/*   Updated: 2025/03/05 16:26:13 by jilustre      ########   odam.nl         */
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
	}
	else if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else
		printf("UNKNOWN\n");

	char left_prefix[256], right_prefix[256];
	snprintf(left_prefix, sizeof(left_prefix), "%s├── L: ", prefix);
	snprintf(right_prefix, sizeof(right_prefix), "%s└── R: ", prefix);
	print_ast(node->left, indent + 1, left_prefix);
	print_ast(node->right, indent + 1, right_prefix);
}

int	main(void)
{
	char		*input = "ls -l | grep txt | wc -l";
	t_source	src;
	t_token		*token;
	t_token		*token_list = NULL;
	t_ast		*ast;
	t_token		*last;
	t_token		*backup;

	src.buffer = input;
	src.bufsize = ft_strlen(input);
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
