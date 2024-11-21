// Assignment name	: ft_strcspn
// Expected files	: ft_strcspn.c
// Allowed functions: None
// ---------------------------------------------------------------

// Reproduce exactly the behavior of the function strcspn
// (man strcspn).

// The function should be prototyped as follows:

// size_t	ft_strcspn(const char *s, const char *reject);

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i = 0;
	size_t	j = 0;

	while(s[i])
	{
		while(reject[j])
		{
			if (reject[j] == s[i])
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}
int main(void)
{
    char s1[] = "hello world";
    char s2[] = "od";

    size_t result = ft_strcspn(s1, s2);

    printf("The initial segment length of '%s' that doesn't contain any characters from '%s' is: %zu\n", s1, s2, result);
    return 0;
}
