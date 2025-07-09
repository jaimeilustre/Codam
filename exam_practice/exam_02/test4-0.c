/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test4-0.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/29 17:29:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/09 08:45:30 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct s_node
{
	char *tag;
	struct s_node *next;
} t_node;

/*Push a tag into the stack*/
void push(t_node **stack, char *tag)
{
	t_node *new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->tag = strdup(tag);
	new->next = *stack;
	*stack = new;
}

/*Pop a tag from the stack*/
char *pop(t_node **stack)
{
	if (!*stack)
		return (NULL);
	t_node *top = *stack;
	char *tag = top->tag;
	*stack = top->next;
	free(top);
	return (tag);
}

/*Free stack*/
void free_stack(t_node **stack)
{
	while (*stack)
	{
		t_node *temp = *stack;
		*stack = (*stack)->next;
		free(temp->tag);
		free(temp);
	}
}

char *extract_tag(const char *str, int *i, int *is_closing)
{
	while (str[*i] && str[*i] != '<')
		(*i)++;
	if (!str[*i])
		return (NULL); // if end of string already, return null
	(*i)++; // skip '<'
	
	*is_closing = 0;
	if (str[*i] == '/')
	{
		*is_closing = 1;
		(*i)++;
	}
	int start = *i; // Pointing to the start of the tag WITHOUT < or /
	while (str[*i] && str[*i] != '>' && !isspace(str[*i])) // Move until the CLOSING TAG >
		(*i)++;
	int len = *i - start; // Grab length of tag
	if (len <= 0)
		return (NULL); // if nothing there, return null
	
	char *tag = malloc(len + 1);
	if (!tag)
		exit (1);
	strncpy(tag, str + start, len); // Copy tag into tag variable
	tag[len] = '\0';
	
	while (str[*i] && str[*i] != '>')
		(*i)++;
	if (str[*i] == '>')
		(*i)++;
	
	return (tag);	
}

bool main_check(const char *input)
{
	t_node *stack = NULL;
	int	i = 0;
	int is_closing;
	char *tag;
	
	while ((tag = extract_tag(input, &i, &is_closing)))
	{
		if (!is_closing)
		{
			if (strcmp(tag, "img") == 0)
			{
				free(tag);
				continue ;
			}
			push(&stack, tag);
		}
		else
		{
			char *open = pop(&stack);
			if (!open || strcmp(open, tag) != 0)
			{
				free(tag);
				free(open);
				free_stack(&stack);
				return (false);
			}
			free(open);
		}
		free(tag);
	}
	if (stack == NULL)
		return (true);
	else
	{
		free_stack(&stack);
		return (false);
	}
}

bool main_check(const char *input)
{
	char stack[512][64];
	int top = -1;

	int i = 0;
	int is_closing;
	char *tag;

	while ((tag = extract_tag(input, &i, &is_closing)))
	{
		if (!is_closing)
		{
			if (strcmp(tag, "img") == 0)
			{
				free(tag);
				continue;
			}
			if (top >= 64 - 1)
			{
				free(tag);
				return false; // Stack overflow
			}
			strncpy(stack[++top], tag, 64 - 1);
			stack[top][64 - 1] = '\0'; // Ensure null-terminated
		}
		else
		{
			if (top < 0 || strcmp(stack[top--], tag) != 0)
			{
				free(tag);
				return false;
			}
		}
		free(tag);
	}
	return top == -1;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	else
	{
		if (main_check(argv[1]))
			return (0);
		else
			return (1);
	}
}
	