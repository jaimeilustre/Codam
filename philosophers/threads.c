/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:10:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/11 17:46:04 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_philo_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philos[i].time_since_last_meal = get_current_time();
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

int	all_philos_ate_enough(t_data *data)
{
	int	i;

	if (data->nb_of_meals_per_philo <= 0)
		return (0);
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten < data->nb_of_meals_per_philo)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*data;
	size_t	meal_time;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			pthread_mutex_lock(&data->meal_mutex);
			meal_time = get_current_time()
				- data->philos[i].time_since_last_meal;
			pthread_mutex_unlock(&data->meal_mutex);
			if (meal_time > (size_t)data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->deaths = 1;
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_lock(&data->print_mutex);
				printf("%lu %d died\n", get_current_time() - data->start_time,
					data->philos[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			i++;
		}
		if (all_philos_ate_enough(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->deaths = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		ft_usleep(1000);
	}
	return (NULL);
}
