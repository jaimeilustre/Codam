/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chunk_creation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:51:39 by jilustre      #+#    #+#                 */
/*   Updated: 2024/12/16 16:16:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calc_chunks(t_chunk_data *data, int **sorted_values, int *chunk_size)
{
	*sorted_values = stack_to_sorted_array(*(data->a), data->total_elements);
	if (data->total_elements > 100)
		*chunk_size = data->total_elements / 20;
	else
		*chunk_size = data->total_elements / 5;
}

void	allocate_chunks(t_chunk_data *data, int *sorted_values, int chunk_size)
{
	int	i;
	int	k;
	int	current_chunk_end;

	*(data->chunks) = malloc(sizeof(int)
			* (data->total_elements / chunk_size + 2));
	if (!*(data->chunks))
	{
		free(sorted_values);
		exit_error(NULL, NULL, NULL);
	}
	k = 0;
	i = 0;
	while (i < data->total_elements)
	{
		if (i + chunk_size < data->total_elements)
			current_chunk_end = i + chunk_size;
		else
			current_chunk_end = data->total_elements;
		(*data->chunks)[k++] = sorted_values[current_chunk_end - 1];
		i += chunk_size;
	}
	(*data->chunks)[k] = INT_MAX;
	*(data->chunk_count) = k;
}

void	process_chunks(t_chunk_data *data)
{
	int	j;
	int	lower_bound;
	int	upper_bound;

	j = 0;
	while (j < *(data->chunk_count))
	{
		if (j == 0)
			lower_bound = INT_MIN;
		else
			lower_bound = (*data->chunks)[j - 1] + 1;
		upper_bound = (*data->chunks)[j];
		while (has_target_in_chunk(*(data->a), lower_bound, upper_bound))
		{
			rotate_to_top(data->a, find_closest(*(data->a),
					lower_bound, upper_bound));
			pb(data->a, data->b, 1);
		}
		j++;
	}
}

void	create_chunks(t_chunk_data *data)
{
	int	*sorted_values;
	int	chunk_size;

	calc_chunks(data, &sorted_values, &chunk_size);
	allocate_chunks(data, sorted_values, chunk_size);
	*(data->chunk_count) = (data->total_elements / chunk_size + 2);
	process_chunks(data);
	free(sorted_values);
}
