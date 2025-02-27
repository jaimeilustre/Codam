/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/27 16:58:56 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*Allocate memory for an Abstract Syntax Tree node*/
t_ast	*allocate_ast_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	node->type = type;
	return (node);
}

/*Create node command*/
t_ast	*create_command_node(char **args)
{
	t_ast	*node;

	node = allocate_ast_node(NODE_COMMAND);
	if (!node)
	{
		free_args(args);
		return (NULL);
	}
	node->args = args;
	return (node);
}

/*Parse simple command and return node command*/
t_ast	*parse_simple_command(t_token **tokens)
{
	char	**args;
	int		i;

	i = arg_count(tokens);
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		args[i] = ft_strdup((*tokens)->value);
		if (!args[i])
		{
			free_args(args);
			return (NULL);
		}
		i++;
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (create_command_node(args));
}

/*Building the pipe in AST*/
t_ast	*create_ast_pipe(t_ast *left, t_token **tokens)
{
	t_ast	*node;

	node = allocate_ast_node(NODE_PIPE);
	if (!node)
	{
		free_ast(left);
		return (NULL);
	}
	node->left = left;
	*tokens = (*tokens)->next;
	node->right = build_ast_tree(tokens);
	if (!node->right)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

/*Building the Abstract Syntax tree*/
t_ast	*build_ast_tree(t_token **tokens)
{
	t_ast	*left;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_simple_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN_PIPE)
			left = create_ast_pipe(left, tokens);
		else
			break ;
	}
	return (left);
}

// #include <stdio.h>

// /*Printing the Abstract Syntax Tree*/
// void	print_ast(t_ast *node, int indent)
// {
// 	int	i;

// 	if (!node)
// 		return ;
// 	i = 0;
// 	while (i < indent)
// 	{
// 		printf(" ");
// 		i++;
// 	}
// 	if (node->type == NODE_COMMAND)
// 	{
// 		printf("COMMAND: ");
// 		if (node->args)
// 		{
// 			i = 0;
// 			while (node->args[i] != NULL)
// 			{
// 				printf("%s ", node->args[i]);
// 				i++;
// 			}
// 		}
// 		printf("\n");
// 	}
// 	else if (node->type == NODE_PIPE)
// 		printf("PIPE\n");
// 	else
// 		printf("UNKNOWN\n");
// 	print_ast(node->left, indent + 1);
// 	print_ast(node->right, indent + 1);
// }

// int	main(void)
// {
// 	char		*input = "ls -l | grep txt | wc -l";
// 	t_source	src;
// 	t_token		*token;
// 	t_token		*token_list = NULL;
// 	t_ast		*ast;
// 	t_token		*last;
// 	t_token		*backup;

// 	src.buffer = input;
// 	src.bufsize = ft_strlen(input);
// 	src.curpos = 0;
// 	while ((token = return_next_token(&src)) != NULL)
// 	{
// 		if (token->type == TOKEN_EOF)
// 		{
// 			free_token(token);
// 			break ;
// 		}
// 		printf("New token created: %s (Type: %d)\n", token->value, token->type);
// 		if (!token_list)
// 		{
// 			token_list = token;
// 			printf("token_list initialized with token: %s\n", token->value);
// 		}
// 		else
// 		{
// 			last->next = token;
// 			printf("Added token to list: %s\n", token->value);
// 		}
// 		last = token;
// 	}
// 	printf("Before AST creation: token_list at %p\n", token_list);
// 	backup = token_list;
// 	ast = build_ast_tree(&token_list);
// 	printf("After AST creation: token_list at %p\n", token_list);
// 	print_ast(ast, 0);
// 	free_token_list(backup);
// 	free_ast(ast);
// 	return (0);
// }
