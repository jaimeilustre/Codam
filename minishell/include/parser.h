/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 16:49:19 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/27 16:21:22 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOF
}	t_token_type;

typedef struct s_source
{
	char	*buffer;	/*input text*/
	long	bufsize;	/*size of the input text*/
	long	curpos;		/*current position in the input text*/
}	t_source;

typedef struct s_token
{
	t_token_type	type;
	int				size;
	char			*value;
	struct s_token	*next;
}	t_token;


typedef enum e_node_type
{
	NODE_COMMAND, // A simple command
	NODE_PIPE,	// A pipeline
	NODE_REDIRECT, // Redirection
	NODE_AND, // Logical &&
	NODE_OR, // Logical ||
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*file;
}	t_ast;

char	next_char(t_source *src);
bool	is_operator(char c);
bool	is_space(char c);
void	free_token(t_token *token);
t_token	*allocate_token(t_token_type type, char *value);

t_token	*create_token(t_token_type type, char *value);
t_token	*return_word_token(t_source *src);
t_token	*return_single_operator_token(char c);
t_token	*return_double_operator_token(t_source *src, char c);
t_token	*return_next_token(t_source *src);

void	free_ast(t_ast *node);
void	free_args(char **args);
int		arg_count(t_token **tokens);
void	free_token_list(t_token *head);

t_ast	*allocate_ast_node(t_node_type type);
t_ast	*create_command_node(char **args);
t_ast	*parse_simple_command(t_token **tokens);
t_ast	*create_ast_pipe(t_ast *left, t_token **tokens);
t_ast	*build_ast_tree(t_token **tokens);

#endif
