/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/27 12:20:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/27 16:28:12 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*Free args array*/
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/*Free Abstract Syntax Tree*/
void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

/*Count args for args array*/
int	arg_count(t_token **tokens)
{
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
		return (0);
	return (i);
}

/*Free tokens after use*/
void	free_token_list(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free_token(temp);
	}
}
