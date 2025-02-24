/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 10:03:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/24 15:24:45 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"

/*Tokenization*/

/*Retrives the next character from the input*/
char next_char(t_source *src)
{
	if (src->curpos >= src->bufsize)
		return ('\0');
	return (src->buffer[src->curpos++]);
}

/*Checks if the input contains an operator*/
bool is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

/*Checks if the input contains any whitespaces*/
bool is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*Free the memory used by the token struct*/
void free_token(t_token *tok)
{
	if (tok->value)
		free(tok->value);
	free(tok);
}

/*Allocate memory for a new token*/
t_token	*create_token(t_token_type type, char *value)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

/*Scans and returns a word token*/
t_token *scan_word_token(t_source *src)
{
    long	start;
	long	length;
	char	*word;
	long	i;

	start = src->curpos - 1;
    while (src->curpos < src->bufsize &&
           !is_space(src->buffer[src->curpos]) &&
           !is_operator(src->buffer[src->curpos])) {
        src->curpos++;
    }
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
    return (create_token(TOKEN_WORD, word));
}

/*Returns the next token from the input, including operators and EOF*/
t_token *get_next_token(t_source *src)
{
	char	c;
	char	*operator;
	char	next;
    
    while ((c = next_char(src)) && is_space(c))
        ;
    if (c == '\0')
        return (create_token(TOKEN_EOF, NULL));
    if (is_operator(c)) 
	{
        operator = malloc(3);
        if (!operator)
            return (free(operator), NULL);
        operator[0] = c;
        operator[1] = '\0';
        operator[2] = '\0';
		next = next_char(src);
		if ((c == '&' && next == '&') || (c == '|' && next == '|'))
		{
            operator[1] = next;
            if (c == '&')
            	return (create_token(TOKEN_AND, operator));
            else
                return (create_token(TOKEN_OR, operator));   
        }
        if ((c == '>' || c == '<') && next == c)
		{
            operator[1] = next;
            if (c == '>')
                return (create_token(TOKEN_APPEND, operator));
            else
                return (create_token(TOKEN_HEREDOC, operator));
        }
		src->curpos--;
        if (c == '>')
            return (create_token(TOKEN_REDIRECT_OUT, operator));
        if (c == '<')
            return (create_token(TOKEN_REDIRECT_IN, operator));
		if (c == '|')
			return (create_token(TOKEN_PIPE, operator));
    }
    return (scan_word_token(src));
}

#include <stdio.h>
#include <string.h>
#include "libft.h"

/*Creating the Abstract Syntax Tree (Parser)*/

t_ast *create_ast_node(t_node_type type)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast *parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	char	**args;
	int		i;
	t_token	*temp;

	/*Count how many arguments*/
	i = 0;
	temp = *tokens;
	while (temp && temp->type == TOKEN_WORD)
	{
		i++;
		temp = temp->next;
	}
	if (i == 0)
		return (NULL);
	/*Allocate memory for an argumets array*/
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	/*Store commands and arguments*/
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
	/*Create AST node for the command*/
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

t_ast	*parse_tokens(t_token **tokens)
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
			node->right = parse_tokens(tokens);
			return (node);
		}
		// else if ((*tokens)->type == TOKEN_REDIRECT_IN || (*tokens)->type == TOKEN_REDIRECT_OUT)
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

void free_ast(t_ast *node)
{
    int i;

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

int main(void)
{
    char input[] = "ls -l | grep txt | wc -l";
    
    t_source src;
	t_token *token;
	t_token *token_list = NULL;
	t_token *last = NULL;
	t_ast	*ast;
	
    src.buffer = input;
    src.bufsize = ft_strlen(input);
    src.curpos = 0;
    while ((token = get_next_token(&src)) != NULL)
	{
        if (token->type == TOKEN_EOF)
		{
            free(token);
            break;
        }
		if (!token_list)
			token_list = token;
		else
			last->next = token;
		last = token;
    }
	ast = parse_tokens(&token_list);
	print_ast(ast, 0);
	// free_token(token_list);
	free_ast(ast);
    return (0);
}
