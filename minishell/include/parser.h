/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 16:49:19 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/24 17:28:57 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "ms_string.h"
# include "list.h"

typedef enum e_syntax_error_code
{
	SYN_EOF = 0,
	SYN_EMPTY_SUBSHELL = 1,
	SYN_CLOSE_PAR = 2,
	SYN_EXPEC_OPEN_PAR = 3,
	SYN_AFT_SUBSHELL = 4,
	SYN_SUBSHELL_AFTER_CMD = 5,
	SYN_NULL_POINTER = 6,
	SYN_NO_DELIMITER = 7,
	SYN_UNCLOSED_QUOTE = 8,
	SYN_UNEXPEC_TOKEN = 9,
	SYN_SYNTAX_ERROR_MAX = 10
}	t_syntax_error;

typedef enum e_token_type
{
	TOKEN_WRD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAR,
	TOKEN_RPAR,
	TOKEN_EOF
}	t_token_type;

typedef struct s_source
{
	char	*buffer;
	long	bufsize;
	long	curpos;
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
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

typedef struct s_redirect
{
	t_node_type			type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
	t_redirect		*redirect;
}	t_ast;

char		peek_char(t_source *src);
char		next_char(t_source *src);
bool		is_double_operator(char c, char d);
bool		is_single_operator(char c);
bool		is_space(char c);

t_token		*create_token(t_token_type type, char *value);
t_token		*create_tokens(t_str cmd);
t_token		*allocate_token(t_token_type type, char *value);
void		free_token(t_token *token);

int			check_quotes(const char *input);
int			read_quotes(t_source *src, long start);
char		*remove_quotes(t_token *token);
bool		check_opening_parenthesis(t_token *tokens);

t_token		*return_word_token(t_source *src);
t_token		*return_single_operator_token(char c);
t_token		*return_double_operator_token(t_source *src, char c);
t_token		*return_next_token(t_source *src);

int			arg_count(t_token *tokens);
void		free_token_list(t_token **head);
void		append_redir(t_ast *left, t_redirect *redir);
t_ast		*choose_redir(t_ast *cmd, t_token **tokens, t_alist *env_lst);
bool		is_valid_token(t_token *token);

t_ast		*allocate_ast_node(t_node_type type);
t_ast		*create_command_node(char **args);
void		free_ast(t_ast *node);
t_redirect	*allocate_ast_redir(t_token *token);
void		add_argument_to_ast(t_ast *left, t_token **tokens);

t_ast		*create_ast_hdoc(t_ast *left, t_token **tokens, t_alist *env_lst);

t_ast		*parse_simple_command(t_token **tokens);
t_ast		*create_ast_pipe(t_ast *left, t_token **tokens, t_alist *env_lst);
t_ast		*create_ast_redir(t_ast *left, t_token **tokens);
t_ast		*create_ast_logic(t_ast *left, t_token **tokens, t_alist *env_lst);
t_ast		*create_ast_subshell(t_token **tokens, t_alist *env_lst);

t_ast		*parse_subshell(t_token **tokens, t_alist *env_lst);
t_ast		*parse_redirections(t_token **tokens, t_alist *env_lst);
t_ast		*parse_pipes(t_token **tokens, t_alist *env_lst);
t_ast		*parse_logical(t_token **tokens, t_alist *env_lst);
t_ast		*build_ast_tree(t_token *tokens, t_alist *env_lst);

void		syntax_error(t_syntax_error code, const char *token);

#endif
