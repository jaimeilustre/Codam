/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:40:03 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/18 07:57:18 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Thinking routine*/
void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

/*Taking forks routine*/
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	if (philo->data->nb_of_philos == 1)
	{
		ft_usleep(philo->data->time_to_die + 10);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
}

/*Eating routine*/
void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->time_since_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

/*Returning forks routine*/
void	return_forks(t_philo *philo)
{
	if (philo->data->nb_of_philos == 1)
		return ;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/*Sleeping routine*/
void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}
