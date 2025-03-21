/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 17:19:15 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/18 10:39:54 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "minishell.h"
#include "exec.h"

// TODO: Implementation needed
static bool	exec_and(t_ast *node, t_exec *exec)
{
	(void)node;
	(void)exec;
	return (true);
}

// TODO: Implementation needed
static bool	exec_or(t_ast *node, t_exec *exec)
{
	(void)node;
	(void)exec;
	return (true);
}

// TODO: add case for type node not supported
bool	exec_node(t_ast *node, t_exec *exec)
{
	if (node == NULL)
		return (true);
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, exec));
	else if (node->type == NODE_AND || node->type == NODE_OR)
		return (exec_and(node, exec));
	else if (node->type == NODE_OR)
		return (exec_or(node, exec));
	else if (node->type == NODE_COMMAND)
		return (exec_cmd(node, exec));
	return (false);
}
