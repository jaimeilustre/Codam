/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parenthesis.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 08:27:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/18 09:11:04 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/*Checks for parenthesis position in input*/
static int	valid_position(const char *input, const char *start, int operator)
{
	if (!(operator || input == start))
	{
		ft_putendl_fd("Syntax error: unexpected token `('", 2);
		return (0);
	}
	return (1);
}

/*Checks for closing parenthesis*/
static int	check_closing_parenthesis(char c, int *depth)
{
	if (c == '(')
		(*depth)++;
	else if (c == ')')
	{
		if (*depth == 0)
		{
			ft_putendl_fd("Syntax error: near unexpected token `)'", 2);
			return (-1);
		}
		(*depth)--;
	}
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
		if (*input == '(' && !valid_position(input, start, operator))
			return (-1);
		else if (check_closing_parenthesis(*input, &depth) == -1)
			return (-1);
		else if (is_operator(*input))
			operator = 1;
		else if (!is_space(*input))
			operator = 0;
		input++;
	}
	if (depth > 0)
	{
		ft_putendl_fd("Syntax error: near unexpected token `('", 2);
		return (-1);
	}
	return (0);
}
