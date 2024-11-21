// Assignment name  : ft_strcmp
// Expected files   : ft_strcmp.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Reproduce the behavior of the function strcmp (man strcmp).

// Your function must be declared as follows:

// int    ft_strcmp(char *s1, char *s2);

#include <string.h>
#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int main(void)
{
	printf("Original vs Clone: %d %d", strcmp("hello World", "hello world"), ft_strcmp("hello World", "hello world"));
	printf("\nOriginal vs Clone: %d %d", strcmp("hello World", ""), ft_strcmp("hello World", ""));
}
