/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parenthesis_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 08:27:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/23 17:32:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/*Checks for parenthesis position in input*/
int	valid_position(const char *input, const char *start, int operator)
{
	if (!(operator || input == start))
	{
		ft_putendl_fd("Syntax error: `(' must follow an operator or start the command", 2);
		return (0);
	}
	return (1);
}

/*Checks for closing parenthesis*/
int	check_closing_parenthesis(char c, int *depth)
{
	if (c == '(')
		(*depth)++;
	else if (c == ')')
	{
		if (*depth == 0)
		{
			ft_putendl_fd("Syntax error: unmatched closing parenthesis `)'", 2);
			return (-1);
		}
		(*depth)--;
	}
	return (0);
}

/*Checks next word*/
static int	check_next_word(const char *input, const char **next)
{
	while (*input && is_space(*input))
		input++;
	if (*input && !is_operator(*input) && *input != ')')
	{
		ft_putendl_fd("Syntax error: expected operator after closing `)'", 2);
		return (-1);
	}
	*next = input;
	return (0);
}

/*Checks for valid subshell content*/
int	check_subshell(const char *input, const char **next, int *valid)
{
	int	depth;

	depth = 1;
	while (*input && depth > 0)
	{
		if (*input == '(')
		{
			if (validate_subshell(input + 1, &input) == -1)
				return (-1);
			*valid = 1;
			continue ;
		}
		else if (*input == ')')
		{
			depth--;
			if (depth == 0)
			{
				if (check_next_word(input + 1, next) == -1)
					return (-1);
				break ;
			}
		}
		else if (!is_space(*input) && !is_operator(*input))
			*valid = 1;
		input++;
	}
	if (depth != 0)
		return (ft_putendl_fd("Syntax error: unmatched opening parenthesis `('", 2), -1);
	return (0);
}
