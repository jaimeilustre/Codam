/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chunk_creation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:51:39 by jilustre      #+#    #+#                 */
/*   Updated: 2025/02/03 15:36:26 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calc_chunks(t_chunk_data *data, int **sorted_arr, int *chunk_size)
{
	*sorted_arr = stack_to_sorted_array(*(data->a), data->total_elements);
	if (data->total_elements > 100)
		*chunk_size = data->total_elements / 20;
	else
		*chunk_size = data->total_elements / 5;
}

void	allocate_chunks(t_chunk_data *data, int *sorted_arr, int chunk_size)
{
	int	i;
	int	j;
	int	current_chunk_end;

	*(data->chunks) = malloc(sizeof(int)
			* (data->total_elements / chunk_size + 2));
	if (!*(data->chunks))
	{
		free(sorted_arr);
		exit_error(NULL, NULL, NULL);
	}
	j = 0;
	i = 0;
	while (i < data->total_elements)
	{
		if (i + chunk_size < data->total_elements)
			current_chunk_end = i + chunk_size;
		else
			current_chunk_end = data->total_elements;
		(*data->chunks)[j++] = sorted_arr[current_chunk_end - 1];
		i += chunk_size;
	}
	(*data->chunks)[j] = INT_MAX;
	*(data->chunk_count) = j;
}

void	process_chunks(t_chunk_data *data)
{
	int	i;
	int	lower_bound;
	int	upper_bound;

	i = 0;
	while (i < *(data->chunk_count))
	{
		if (i == 0)
			lower_bound = INT_MIN;
		else
			lower_bound = (*data->chunks)[i - 1] + 1;
		upper_bound = (*data->chunks)[i];
		while (has_target_in_chunk(*(data->a), lower_bound, upper_bound))
		{
			rotate_to_top(data->a, find_closest(*(data->a),
					lower_bound, upper_bound));
			pb(data->a, data->b, 1);
		}
		i++;
	}
}

void	create_chunks(t_chunk_data *data)
{
	int	*sorted_arr;
	int	chunk_size;

	calc_chunks(data, &sorted_arr, &chunk_size);
	allocate_chunks(data, sorted_arr, chunk_size);
	process_chunks(data);
	free(sorted_arr);
}
