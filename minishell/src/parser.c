/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/26 16:29:35 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include "libft.h"

/*Tokenization*/

/*Retrives the next character from the input*/
char	next_char(t_source *src)
{
	if (src->curpos >= src->bufsize)
		return ('\0');
	return (src->buffer[src->curpos++]);
}

/*Checks if the input contains an operator*/
bool	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

/*Checks if the input contains any whitespaces*/
bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*Free the memory used by the token struct*/
void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

/*Allocate memory for a new token*/
t_token	*allocate_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}

/*Scans and returns a word token*/
t_token	*create_word_token(t_source *src)
{
	long	start;
	long	length;
	char	*word;
	long	i;
	t_token	*word_token;

	start = src->curpos - 1;
	while (src->curpos < src->bufsize && !is_space(src->buffer[src->curpos])
		&& !is_operator(src->buffer[src->curpos]))
		src->curpos++;
	length = src->curpos - start;
	word = malloc(length + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = src->buffer[start + i];
		i++;
	}
	word[length] = '\0';
	word_token = allocate_token(TOKEN_WORD, word);
	if (!word_token)
		return (free(word), NULL);
	return (word_token);
}

/*Returns the next token from the input, including operators and EOF*/
t_token	*create_operator_token(t_source *src)
{
	char	c;
	char	*operator;
	char	next;
	t_token	*token;

	while ((c = next_char(src)) && is_space(c))
		;
	if (c == '\0')
	{
		token = allocate_token(TOKEN_EOF, NULL);
		return (token);
	}
	if (is_operator(c))
	{
		next = next_char(src);
		if ((c == '>' || c == '<') && next == c)
		{
			operator = ft_strdup((char []){c, next, '\0'});
			if (!operator)
				return (NULL);
			if (c == '>')
			{
				token = allocate_token(TOKEN_APPEND, operator);
				if (!token)
					free(operator);
				return (token);
			}
			else
			{
				token = allocate_token(TOKEN_HEREDOC, operator);
				if (!token)
					free(operator);
				return (token);
			}
		}
		if ((c == '&' && next == '&') || (c == '|' && next == '|'))
		{
			operator = ft_strdup((char []){c, next, '\0'});
			if (!operator)
				return (NULL);
			if (c == '&')
			{
				token = allocate_token(TOKEN_AND, operator);
				if (!token)
					free(operator);
				return (token);
			}
			else
			{
				token = allocate_token(TOKEN_OR, operator);
				if (!token)
					free(operator);
				return (token);
			}
		}
		src->curpos--;
		operator = ft_strdup((char []){c, '\0'});
		if (!operator)
			return (NULL);
		if (c == '>')
			return (allocate_token(TOKEN_REDIRECT_OUT, operator));
		if (c == '<')
			return (allocate_token(TOKEN_REDIRECT_IN, operator));
		if (c == '|')
			return (allocate_token(TOKEN_PIPE, operator));
	}
	return (create_word_token(src));
}

/*Creating the Abstract Syntax Tree (Parser)*/
t_ast	*create_ast_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->file = NULL;
	return (node);
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (node->args)
	{
		i = 0;
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	char	**args;
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tokens;
	while (temp && temp->type == TOKEN_WORD)
	{
		i++;
		temp = temp->next;
	}
	if (i == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		args[i] = ft_strdup((*tokens)->value);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		i++;
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	node = create_ast_node(NODE_COMMAND);
	if (!node)
	{
		while (--i >= 0)
			free(args[i]);
		free(args);
		return (NULL);
	}
	node->args = args;
	return (node);
}

t_ast	*create_ast_tree(t_token **tokens)
{
	t_ast	*left;
	t_ast	*node;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_simple_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN_PIPE)
		{
			node = create_ast_node(NODE_PIPE);
			node->left = left;
			*tokens = (*tokens)->next;
			node->right = create_ast_tree(tokens);
			return (node);
		}
		else
			break ;
	}
	return (left);
}

void	print_ast(t_ast *node, int indent)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < indent)
	{
		printf(" ");
		i++;
	}
	if (node->type == NODE_COMMAND)
	{
		printf("COMMAND: ");
		if (node->args)
		{
			i = 0;
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
	print_ast(node->left, indent + 1);
	print_ast(node->right, indent + 1);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_token(tmp);
	}
}

int	main(void)
{
	char		*input = "ls -l | grep txt | wc -l";
	t_source	src;
	t_token		*token;
	t_token		*token_list = NULL;
	t_ast		*ast;
	t_token		*last;
	t_token		*backup = token_list;

	src.buffer = input;
	src.bufsize = ft_strlen(input);
	src.curpos = 0;
	while ((token = create_operator_token(&src)) != NULL)
	{
		if (token->type == TOKEN_EOF)
		{
			free_token(token);
			break ;
		}
		printf("New token created: %s (Type: %d)\n", token->value, token->type);
		if (!token_list)
		{
			token_list = token;
			printf("token_list initialized with token: %s\n", token->value);
		}
		else
		{
			last->next = token;
			printf("Added token to list: %s\n", token->value);
		}
		last = token;
	}
	printf("Before AST creation: token_list at %p\n", token_list);
	ast = create_ast_tree(&token_list);
	printf("After AST creation: token_list at %p\n", token_list);
	print_ast(ast, 0);
	free_token_list(backup);
	free_ast(ast);
	return (0);
}
