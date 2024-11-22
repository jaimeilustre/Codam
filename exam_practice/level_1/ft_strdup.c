// Assignment name  : ft_strdup
// Expected files   : ft_strdup.c
// Allowed functions: malloc
// --------------------------------------------------------------------------------

// Reproduce the behavior of the function strdup (man strdup).

// Your function must be declared as follows:

// char    *ft_strdup(char *src);

#include <stdlib.h>
#include <stdio.h>

char *ft_strdup(char *src)
{
	int	len = 0;
	int	i = 0;
	char *dest;
	
	while (src[len])
		len++;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	main(void)
{
	char *src = "Hello, world!";
	
	printf("%s", ft_strdup(src));
	return (0);
}
