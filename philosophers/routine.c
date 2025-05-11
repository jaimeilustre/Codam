/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:40:03 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/11 17:37:29 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

void	print_message(t_philo *philo, char *msg)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%lu %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->time_since_last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

void	return_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->deaths)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		think(philo);
		take_forks(philo);
		eat(philo);
		return_forks(philo);
		sleeping(philo);
		if (philo->data->nb_of_meals_per_philo > 0
			&& philo->meals_eaten >= philo->data->nb_of_meals_per_philo)
			break ;
	}
	return (NULL);
}
