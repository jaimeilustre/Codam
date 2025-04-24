/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_errors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 13:55:51 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/24 16:36:40 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

#define MS_MESSAGE_SIZE 2048

static const char	*g_syntax_errors[] = {
	"unexpected end of file",
	"empty subshell",
	"expected closing parenthesis `)'",
	"expected opening parenthesis `('",
	"unexpected token after subshell",
	"unexpected subshell after command",
	"NULL pointer as first token",
	"near unexpected token `newline'",
	"near unexpected token `quote'",
	"near unexpected token",
};

void	syntax_error(t_syntax_error code, const char *token)
{
	char	message[MS_MESSAGE_SIZE];

	if (code < 0 || code >= SYN_SYNTAX_ERROR_MAX)
		code = SYN_UNEXPEC_TOKEN;
	ft_bzero(message, sizeof(message));
	ft_strlcat(message, "minishell: syntax error: ", MS_MESSAGE_SIZE);
	ft_strlcat(message, g_syntax_errors[code], MS_MESSAGE_SIZE);
	if (token)
	{
		ft_strlcat(message, " `", MS_MESSAGE_SIZE);
		ft_strlcat(message, token, MS_MESSAGE_SIZE);
		ft_strlcat(message, "'", MS_MESSAGE_SIZE);
	}
	ft_putendl_fd(message, STDERR);
}
