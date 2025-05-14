/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:40:03 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/14 14:30:27 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

/*Thinking routine*/
void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

/*Taking forks routine*/
void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message(philo, "has taken a fork");
	if (philo->data->nb_of_philos == 1)
	{
		ft_usleep(philo->data->time_to_die + 10);
		sem_post(philo->data->forks);
		return ;
	}
	sem_wait(philo->data->forks);
	print_message(philo, "has taken a fork");
}

/*Eating routine*/
void	eat(t_philo *philo)
{
	sem_wait(philo->data->meal_sem);
	philo->time_since_last_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->data->meal_sem);
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

/*Returning forks routine*/
void	return_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

/*Sleeping routine*/
void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}
