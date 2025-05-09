/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:10:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/09 17:31:19 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdbool.h>

bool	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}
