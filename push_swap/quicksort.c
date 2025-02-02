/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quicksort.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:54:07 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/02 17:35:08 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	partition_array(int *arr, int left, int right)
{
	int	pivot_value;
	int	partition_index;
	int	current_index;
	int	temp;

	pivot_value = arr[right];
	partition_index = left - 1;
	current_index = left;
	while (current_index < right)
	{
		if (arr[current_index] <= pivot_value)
		{
			partition_index++;
			temp = arr[partition_index];
			arr[partition_index] = arr[current_index];
			arr[current_index] = temp;
		}
		current_index++;
	}
	temp = arr[partition_index + 1];
	arr[partition_index + 1] = arr[right];
	arr[right] = temp;
	return (partition_index + 1);
}

void	quicksort(int *arr, int left, int right)
{
	int	pivot_index;

	if (left < right)
	{
		pivot_index = partition_array(arr, left, right);
		quicksort(arr, left, pivot_index - 1);
		quicksort(arr, pivot_index + 1, right);
	}
}

int	*stack_to_sorted_array(t_list *a, int stack_size)
{
	int		*arr;
	int		i;
	t_list	*node;

	arr = malloc(sizeof(int) * stack_size);
	if (!arr)
		exit_error(&a, NULL, NULL);
	node = a;
	i = 0;
	while (node)
	{
		arr[i++] = node->content;
		node = node->next;
	}
	quicksort(arr, 0, stack_size - 1);
	return (arr);
}
