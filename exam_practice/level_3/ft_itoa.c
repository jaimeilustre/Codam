// Assignment name  : ft_itoa
// Expected files   : ft_itoa.c
// Allowed functions: malloc
// --------------------------------------------------------------------------------

// Write a function that takes an int and converts it to a null-terminated string.
// The function returns the result in a char array that you must allocate.

// Your function must be declared as follows:

// char	*ft_itoa(int nbr);

#include <stdlib.h>
#include <stdio.h>

int	count_digits(int nb)
{
	int len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char *ft_itoa(int nbr)
{
	char *str;
	
	int len = count_digits(nbr);
	str = malloc(len + 1);
	str[len] = '\0';
	if (nbr == 0)
		str[0] = '0';
	else if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		len--;
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}

int main(void)
{
	printf("%s\n", ft_itoa(100));
	return (0);
}