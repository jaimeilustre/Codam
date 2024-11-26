// Assignment name  : ft_range
// Expected files   : ft_range.c
// Allowed functions: malloc
// --------------------------------------------------------------------------------

// Write the following function:

// int     *ft_range(int start, int end);

// It must allocate (with malloc()) an array of integers, fill it with consecutive
// values that begin at start and end at end (Including start and end !), then
// return a pointer to the first value of the array.

// Examples:

// - With (1, 3) you will return an array containing 1, 2 and 3.
// - With (-1, 2) you will return an array containing -1, 0, 1 and 2.
// - With (0, 0) you will return an array containing 0.
// - With (0, -3) you will return an array containing 0, -1, -2 and -3.

#include <stdlib.h>
#include <stdio.h>

int	*ft_range(int start, int end)
{
	int size = (end >= start) ? (end - start + 1) : (start - end + 1);
	int	*tab = (int *)malloc(sizeof(int) * size);
	int	step = (end >= start) ? 1 : -1;
	int	i = 0;

	if (!tab)
		return (NULL);
	while (i < size)
	{
		tab[i] = start;
		start += step;
		i++;
	}

	return (tab);
}

int	main(void)
{
	int	start = 5;
	int	end = -10;
	int	*tab = ft_range(start, end);
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