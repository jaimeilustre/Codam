/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:40:03 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/16 17:32:08 by jilustre      ########   odam.nl         */
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
	sem_post(philo->data->meal_sem);
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	if (philo->data->max_meals > 0 && philo->meals_eaten
		== philo->data->max_meals)
		sem_post(philo->data->all_meals_sem);
}

/*Returning forks routine*/
void	return_forks(t_philo *philo)
{
	if (philo->data->nb_of_philos == 1)
		return ;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

/*Sleeping routine*/
void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}
