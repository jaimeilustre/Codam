/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/17 14:30:37 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/17 16:20:41 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include "philo.h"

/*Closes the semaphores*/
void	free_and_close(t_data *data)
{
	if (data->forks_sem_init)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
	}
	if (data->meal_sem_init)
	{
		sem_close(data->meal_sem);
		sem_unlink("/meal");
	}
	if (data->print_sem_init)
	{
		sem_close(data->print_sem);
		sem_unlink("/print");
	}
	if (data->death_sem_init)
	{
		sem_close(data->death_sem);
		sem_unlink("/death");
	}
	if (data->all_meals_sem_init)
	{
		sem_close(data->all_meals_sem);
		sem_unlink("/meals");
	}
}

/*Frees the philos array*/
void	free_philos(t_data *data)
{
	if (data->philos)
		free(data->philos);
}
