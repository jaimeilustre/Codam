/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:54:07 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/13 15:37:25 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	partition(int *array, int left, int right)
{
	int	pivot;
	int	i;
	int	j;
	int	temp;

	pivot = array[right];
	i = left - 1;
	j = left;
	while (j < right)
	{
		if (array[j] <= pivot)
		{
			i++;
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
		j++;
	}
	temp = array[i + 1];
	array[i + 1] = array[right];
	array[right] = temp;
	return (i + 1);
}

void	quick_sort(int *array, int left, int right)
{
	int	pivot;

	if (left < right)
	{
		pivot = partition(array, left, right);
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}

int	*stack_to_sorted_array(t_list *a, int size)
{
	int		*array;
	int		i;
	t_list	*current;

	array = malloc(sizeof(int) * size);
	i = 0;
	current = a;
	if (!array)
		exit_error(&a, NULL, NULL);
	while (current)
	{
		array[i++] = current->content;
		current = current->next;
	}
	quick_sort(array, 0, size - 1);
	return (array);
}
