/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:10:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/17 16:31:30 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philo.h"

/*Creates philo threads*/
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

/*Checks if everyone ate their max meals already*/
static bool	max_meals_reached(t_data *data)
{
	int		i;
	bool	result;

	result = true;
	if (data->max_meals <= 0)
		return (false);
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			result = false;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (result);
}

/*Checks for philosopher death and updates flag and message*/
static bool	check_philosopher_death(t_data *data)
{
	int		i;
	size_t	meal_time;

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
			return (true);
		}
		i++;
	}
	return (false);
}

/*Monitor thread*/
void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_philosopher_death(data))
			return (NULL);
		if (max_meals_reached(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->deaths = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}
