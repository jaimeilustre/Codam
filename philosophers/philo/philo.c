/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 08:08:10 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/12 15:03:52 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>

void	free_and_destroy(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

static bool	death_check(t_data *data)
{
	bool	status;

	pthread_mutex_lock(&data->death_mutex);
	status = data->deaths;
	pthread_mutex_unlock(&data->death_mutex);
	return (status);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (death_check(philo->data))
			break ;
		think(philo);
		take_forks(philo);
		eat(philo);
		return_forks(philo);
		if (death_check(philo->data))
			break ;
		sleeping(philo);
		if (philo->data->max_meals > 0
			&& philo->meals_eaten >= philo->data->max_meals)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	int			i;

	if (!parse_args(argc, argv, &data))
		printf("Error with parsing\n");
	if (!init_data(&data))
		printf("Error with initialising\n");
	if (!init_mutex(&data))
		printf("Error with mutex\n");
	init_philos(&data);
	data.start_time = get_current_time();
	if (!create_philo_thread(&data))
		printf("Error with creating philo thread\n");
	if (pthread_create(&monitor_thread, NULL, monitor, &data) != 0)
		printf("Error with creating monitor thread\n");
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data.nb_of_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	free_and_destroy(&data);
	return (0);
}
