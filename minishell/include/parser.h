/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 16:49:19 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/18 14:56:21 by jilustre      ########   odam.nl         */
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
}	t_token;

typedef struct s_ast
{
	int				type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

#endif
