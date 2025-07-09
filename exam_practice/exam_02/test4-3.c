/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test4-3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/08 21:17:45 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/08 21:29:02 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int check_unclosed_quotes(const char *str)
{
	int in_single = 0;
	int in_double = 0;
	
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
	}
	return (in_single == 0 && in_double == 0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (check_unclosed_quotes(argv[1]))
		printf("VALID\n");
	else
		printf("INVALID\n");
	return (0);
}

// int check_unclosed_quotes(const char *str, char quote)
// {
// 	int count = 0;
// 	for (int i = 0; str[i]; i++)
// 	{
// 		if (str[i] == quote)
// 			count++;
// 	}
// 	return (count % 2 == 0);
// }

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (1);

// 	int single_ok = check_unclosed_quotes(argv[1], '\'');
// 	int double_ok = check_unclosed_quotes(argv[1], '\"');
	
// 	if (single_ok && double_ok)
// 		printf("VALID\n");
// 	else
// 		printf("INVALID\n");
// 	return (0);
// }