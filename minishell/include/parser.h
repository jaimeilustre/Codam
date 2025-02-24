/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 16:49:19 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/24 14:44:35 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

#endif
