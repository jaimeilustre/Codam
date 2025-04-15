/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 16:49:19 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/15 14:08:51 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "ms_string.h"
# include "list.h"

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
	char	*buffer;
	long	bufsize;
	long	curpos;
}	t_source;

typedef struct s_token
{
	t_token_type	type;
	int				size;
	char			*value;
	int				quoted;
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

char		next_char(t_source *src);
bool		is_operator(char c);
bool		is_space(char c);

t_token		*create_token(t_token_type type, char *value);
t_token		*create_tokens(t_str cmd);
t_token		*allocate_token(t_token_type type, char *value);
void		free_token(t_token *token);

int			check_quotes(const char *input);
int			read_quotes(t_source *src, long start);
char		*remove_quotes(t_token *token);

t_token		*return_word_token(t_source *src);
t_token		*return_single_operator_token(char c);
t_token		*return_double_operator_token(t_source *src, char c);
t_token		*return_next_token(t_source *src);

int			arg_count(t_token *tokens);
void		free_token_list(t_token **head);
void		append_redir(t_ast *left, t_redirect *redir);
bool		is_valid_next_token(t_token *token);

t_ast		*allocate_ast_node(t_node_type type);
t_ast		*create_command_node(char **args);
void		free_ast(t_ast *node);
t_redirect	*allocate_ast_redir(t_token *token);
void		add_argument_to_ast(t_ast *left, t_token **tokens);

t_redirect	*initialize_heredoc(t_ast *left, t_token **tokens);
int			check_delimiter(t_redirect *redir, t_token *tokens, int *in_quotes);
int			heredoc_exp(t_strb *sb, const char *line, int quoted, t_alist *env_lst);
int			heredoc_input(t_redirect *redir, int quoted, t_alist *env_lst);
t_ast		*create_ast_heredoc(t_ast *left, t_token **tokens, t_alist *env_lst);

t_ast		*parse_simple_command(t_token **tokens);
t_ast		*create_ast_pipe(t_ast *left, t_token **tokens, t_alist *env_lst);
t_ast		*create_ast_redir(t_ast *left, t_token **tokens);
t_ast		*create_ast_logical(t_ast *left, t_token **tokens, t_alist *env_lst);

t_ast		*parse_redirections(t_token **tokens, t_alist *env_lst);
t_ast		*parse_pipes(t_token **tokens, t_alist *env_lst);
t_ast		*parse_logical(t_token **tokens, t_alist *env_lst);
t_ast		*build_ast_tree(t_token **tokens, t_alist *env_lst);

#endif
