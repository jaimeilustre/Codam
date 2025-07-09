/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test4-2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 15:55:49 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/08 21:16:46 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int is_match(char open, char close)
{
	return ((open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}'));
}

int check_brackets(const char *str)
{
	char stack[1024];
	int top = -1;

	for (int i = 0; str[i]; i++)
	{
		char c = str[i];
		if (c == '(' || c == '[' || c == '{')
		{
			if (top >= 1024 - 1)
				return (0);
			stack[++top] = c;
		}
		else if (c == ')' || c == ']' || c == '}')
		{
			if (top < 0 || !is_match(stack[top--], c))
				return (0);
		}
	}
	return (top == -1);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	else
	{
		const char *input = argv[1];
		printf("%s\n", check_brackets(input) ? "VALID" : "INVALID");
		return (0);
	}
}
