// Assignment name  : ft_swap
// Expected files   : ft_swap.c
// Allowed functions: 
// --------------------------------------------------------------------------------

// Write a function that swaps the contents of two integers the adresses of which
// are passed as parameters.

// Your function must be declared as follows:

// void	ft_swap(int *a, int *b);

#include <stdio.h>

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	main(void)
{
	int	n1 = 9;
	int	n2 = 6;
	int	*a = &n1;
	int	*b = &n2;
	
	printf("%i, %i", *a, *b);
	ft_swap(a, b);
	printf("\n");
	printf("%i, %i", *a, *b);
	printf("\n");
	return (0);
}