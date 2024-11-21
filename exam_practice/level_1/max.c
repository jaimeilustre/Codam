// Assignment name  : max
// Expected files   : max.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write the following function:

// int		max(int* tab, unsigned int len);

// The first parameter is an array of int, the second is the number of elements in
// the array.

// The function returns the largest number found in the array.

// If the array is empty, the function returns 0.

#include <stdio.h>

int	max(int *tab, unsigned int len)
{
	unsigned int i = 0;
	int	res = tab[0];

	if (len == 0)
		return (0);
	while (i < len)
	{
		if (res < tab[i])
			res = tab[i];
		i++;
	}
	return (res);
}

int	main(void)
{
	int arr[] = {42, -7, 0, 13, 2, 23, -1, 55};
	unsigned int len = sizeof(arr) / sizeof(arr[0]);

	printf("Array: ");
	for (unsigned int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	int max_value = max(arr, len);
	printf("Maximum value: %d\n", max_value);

	return (0);
}
