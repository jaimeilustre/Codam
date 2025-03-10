// Assignment name  : ft_rrange
// Expected files   : ft_rrange.c
// Allowed functions: malloc
// --------------------------------------------------------------------------------

// Write the following function:

// int     *ft_rrange(int start, int end);

// It must allocate (with malloc()) an array of integers, fill it with consecutive
// values that begin at end and end at start (Including start and end !), then
// return a pointer to the first value of the array.

// Examples:

// - With (1, 3) you will return an array containing 3, 2 and 1
// - With (-1, 2) you will return an array containing 2, 1, 0 and -1.
// - With (0, 0) you will return an array containing 0.
// - With (0, -3) you will return an array containing -3, -2, -1 and 0.

#include <stdlib.h>
#include <stdio.h>

int	*ft_rrange(int start, int end)
{
	int size = (end >= start) ? (end - start + 1) : (start - end + 1);
	int	*tab = (int *)malloc(sizeof(int) * size);
	int	step = (end >= start) ? -1 : 1;
	int	i = 0;

	if (!tab)
		return (NULL);
	while (i < size)
	{
		tab[i] = end;
		end += step;
		i++;
	}

	return (tab);
}

int	main(void)
{
	int	start = 5;
	int	end = -10;
	int	*tab = ft_rrange(start, end);
	int	i = 0;
	int size = (end >= start) ? (end - start + 1) : (start - end + 1);
	if (tab)
	{
		while (i < size)
		{
			printf("%d\n", tab[i]);
			i++;
		}
	}
	return (0);
}