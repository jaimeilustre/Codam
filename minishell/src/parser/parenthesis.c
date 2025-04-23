/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parenthesis.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 15:51:35 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/23 17:32:19 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/*Checks for for valid subshell overall*/
int	validate_subshell(const char *input, const char **next)
{
	int			valid_content;

	valid_content = 0;
	if (check_subshell(input, next, &valid_content) == -1)
		return (-1);
	if (!valid_content)
	{
		ft_putendl_fd("Syntax error: subshell is empty or contains only whitespace/operators", 2);
		return (-1);
	}
	return (0);
}

int	open_parenthesis(const char **input, const char *start, int *operator)
{
	const char	*after_subshell;

	if (!valid_position(*input, start, *operator))
		return (-1);
	if (validate_subshell(*input + 1, &after_subshell) == -1)
		return (-1);
	*input = after_subshell;
	*operator = 0;
	return (0);
}

/*Checking for unclosed parenthesis and position before tokenization*/
int	check_parenthesis(const char *input)
{
	int			depth;
	int			operator;
	const char	*start;

	depth = 0;
	operator = 1;
	start = input;
	while (*input)
	{
		if (*input == '(')
		{
			if (open_parenthesis(&input, start, &operator) == -1)
				return (-1);
			continue ;
		}
		else if (check_closing_parenthesis(*input, &depth) == -1)
			return (-1);
		else if (is_operator(*input))
			operator = 1;
		else if (!is_space(*input))
			operator = 0;
		input++;
	}
	if (depth > 0)
		return (ft_putendl_fd("Syntax error: missing closing `)` for subshell", 2), -1);
	return (0);
}
