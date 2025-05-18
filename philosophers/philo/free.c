/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 08:01:08 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/05/18 08:02:16 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "philo.h"

/*Frees the forks array and destroys the mutexes*/
void	free_and_destroy(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			if (data->forks_init && data->forks_init[i])
				pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->forks_init)
		free(data->forks_init);
	if (data->philos)
		free(data->philos);
	if (data->meal_mutex_init)
		pthread_mutex_destroy(&data->meal_mutex);
	if (data->print_mutex_init)
		pthread_mutex_destroy(&data->print_mutex);
	if (data->death_mutex_init)
		pthread_mutex_destroy(&data->death_mutex);
}
