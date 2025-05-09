/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:40:03 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/09 17:21:20 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

void	print_message(t_philo *philo, char *msg)
{
	int	timestamp;

	pthread_mutex_lock(&philo->data->print);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%d %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printf(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->time_since_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_message(philo, "is eating");
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
}

void	return_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		return_forks(philo);
		sleep(philo);
	}
	return (NULL);
}
